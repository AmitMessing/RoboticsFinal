#include "Particle.h"
#include <math.h>
#include "../ConfigurationManager.h"

Particle::Particle(double x, double y, double pYaw, double bel, Map* map) : _xPos(x), _yPos(y), _yaw(pYaw), _belief(bel)
{
	_map = map;
}

Map* Particle::getMap()
{
	return _map;
}

double Particle::getBelief()
{
	return _belief;
}

void Particle::update(double deltaX, double deltaY, double deltaYaw, Robot* robot)
{
	_xPos += deltaX;
	_yPos += deltaY;
	_yaw += deltaYaw;

	// Get the predicted belief
	double predictedBelief = _belief * calcNewLocationProbability(deltaX, deltaY, deltaYaw);
	// Get the observations probability
	double obsProb = calcObservationsAccuracy(robot);

	// Calculate new belief - according to the predicted belief and observations
	_belief = NORMALIZE_FACTOR * predictedBelief * obsProb;

	if (_belief > 1)
		_belief = 1;
}

double Particle::calcNewLocationProbability(double deltaX, double deltaY, double deltaYaw)
{
	// Calculate the distance passed from the previous location
	double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	// If the robot did not change its orientation and did not move more than the threshold,
	// we are fully sure.
	if ((deltaYaw == 0) && (distance < DIS_THRESHOLD))
	{
		return 1;
	}
	// If the robot did not change its orientation more than the threshold
	// and did not move more than the threshold, we are almost sure.
	else if ((distance < DIS_THRESHOLD) && (deltaYaw < YAW_ANGLE_THRESHOLD))
	{
		return 0.8;
	}
	// If the robot did not change its orientation more than the threshold
	// or it did not move more than the threshold, we are not so sure.
	else if (((distance > DIS_THRESHOLD) && (deltaYaw < YAW_ANGLE_THRESHOLD)) ||
			 ((distance < DIS_THRESHOLD) && (deltaYaw > YAW_ANGLE_THRESHOLD)))
	{
		return 0.5;
	}
	// If the robot changed its orientation more than the threshold
	// and it moved more than the threshold, we are not sure about the robot's location.
	else
	{
		return 0.2;
	}
}

double Particle::calcObservationsAccuracy(Robot* robot)
{
	double numOfWrongMapCells = 0;
	double numOfRightMapCells = 0;

	for (int i=0; i< MAX_LASER_INDEX; i+=5)
	{
		double laserAngle = laserIndexToLaserAngle(i);
		double disFromObstacle = robot->getLaserScan(i);
		double obstacleXPos = _xPos + (disFromObstacle * cos(_yaw + laserAngle));
		double obstacleYPos = _yPos + (disFromObstacle * sin(_yaw + laserAngle));

		// Get the value in the map's cell that represents the obstacle location
		int col = obstacleXPos / ConfigurationManager::GetGridRosolution();
		int row = obstacleYPos / ConfigurationManager::GetGridRosolution();
		char obstacleCurrCellValue = this->_map->GetMapValue(row,col);

		// if the distance is too large, assume that there is no obstacle in this index and don't update the map
		// and if the distance is too short don't consider it as an obstacle because its the robot itself
		if (disFromObstacle < 4.0 && disFromObstacle > 0.2)
		{
			switch (obstacleCurrCellValue)
			{
				case FREE_CELL:
					numOfWrongMapCells ++;
					_map->SetMapValue(obstacleXPos, obstacleYPos, OCCUPIED_CELL);
					break;
				case OCCUPIED_CELL:
					numOfRightMapCells ++;
					break;
				case UNKNOWN_CELL:
					_map->SetMapValue(obstacleXPos, obstacleYPos, OCCUPIED_CELL);
					break;
				default:
					break;
			}
		}

		freeCellsToObstacle(obstacleXPos, obstacleYPos, disFromObstacle);
	}

	// Set free in the particle's position
	_map->SetMapValue(_xPos, _yPos, FREE_CELL);

	return numOfWrongMapCells == 0 ? 1 : (numOfRightMapCells / (numOfRightMapCells + numOfWrongMapCells));
}

void Particle::freeCellsToObstacle(double obstacleXPos, double obstacleYPos, double distanceToObstacle)
{
	double xDifference = obstacleXPos - _xPos;
	double yDifference = obstacleYPos - _yPos;
	double angleToObstacle = atan(yDifference / xDifference);

	double xProgressRatio = abs(cos(angleToObstacle));
	if (obstacleXPos < _xPos)
	{
		xProgressRatio = -xProgressRatio;
	}

	double yProgressRatio = abs(sin(angleToObstacle));
	if (obstacleYPos < _yPos)
	{
		yProgressRatio = -yProgressRatio;
	}

	// Set free cells in the free space between the robot and the obstacle
	for (double j=0; j < distanceToObstacle; j++)
	{
		_map->SetMapValue(_xPos + j*xProgressRatio, _yPos + j*yProgressRatio, FREE_CELL);
	}
}

double Particle::laserIndexToLaserAngle(int index)
{
	return ((index * 0.36 - 120.0) / 180.0) * M_PI;
}

Particle* Particle::createNewParticle()
{
	double angle = (rand() % 360) * M_PI / 180.0;
	double yawAngle = (rand() % NEW_PARTICLE_ANGLE_LIMIT - 30.0) * M_PI / 180.0;

	double newX = _xPos + cos(angle) * NEW_PARTICLE_RADIUS;
	double newY = _yPos + sin(angle) * NEW_PARTICLE_RADIUS;
	double newYaw = _yaw + yawAngle;

	return new Particle(newX, newY, newYaw, _belief, _map);
}

Particle::~Particle()
{
}
