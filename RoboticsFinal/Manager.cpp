#include "Manager.h"
#include <math.h>
#include <vector>
#include "Constants.h"

using namespace std;

Manager::Manager(Robot* robot, vector<Location> wayPoints)
{
	_robot = robot;
	_wayPoints = wayPoints;
	//_currBehavior = _plan->startBehavior();
}

void Manager::run()
{
    unsigned wayIndex = 0;
    this->_robot->Read();

    Location prev = this->_wayPoints[wayIndex];
    Location next = this->_wayPoints[++wayIndex];

    ChangeDirection(prev,next,true);

    cout << "-----------------------------------" << endl << endl;

    double distance, prevDistance;
    while (wayIndex < this->_wayPoints.size())
    {
    	this->_robot->Read();
    	distance = this->CalcDistance(this->_robot->GetLocation(),next);
    	Location l = this->_robot->GetLocation();
    	cout << "( " << l.x << " , " << l.y << ")\t"  << l.yaw << "\t| " << distance << endl;

    	if (distance <= TOLERANCE_DISTANCE)
    	{
    		this->_robot->setSpeed(FORWARD_SPEED_SLOW,0);
    		prevDistance = distance;
    		distance = this->CalcDistance(this->_robot->GetLocation(),next);
    		while (distance <= prevDistance)
    		{
    	    	this->_robot->Read();
        		this->_robot->setSpeed(FORWARD_SPEED,0);
        		prevDistance = distance;
    	    	distance = this->CalcDistance(this->_robot->GetLocation(),next);
    	    	cout << "\t( " << l.x << " , " << l.y << ")\t"  << l.yaw << "\t| " << distance << endl;
    		}

    		this->_robot->setSpeed(0,0);
    	    prev = this->_wayPoints[wayIndex];
    	    next = this->_wayPoints[++wayIndex];
    	    ChangeDirection(prev,next,true);
    	}
    	else
    	{
    		this->_robot->setSpeed(FORWARD_SPEED,0);
    	}
    }

    cout << "Goal point reached successfully" << endl;
}

double Manager::CalcDistance(Location prev, Location next){
	return sqrt((pow(prev.y -  next.y, 2) + (pow(prev.x - next.x, 2))));
}


void Manager::ChangeDirection(Location prev, Location next, bool startPoint)
{
    double angleDelta = this->CalcDelta(prev,next);
    while (abs(angleDelta) >= 0.005)
	{
		this->_robot->Read();
		this->_robot->setSpeed(0,this->CalcDelta(prev,next));
		angleDelta = this->CalcDelta(prev,next);

	}
	if (startPoint)
	{
		this->_robot->setSpeed(0,0);
	}
}

int Manager::CalcNextStep(Location prev, Location next)
{
	int direction;

	// up
	if (next.y > prev.y)
	{
		if (next.x > prev.x)
		{
			direction = DOWN_RIGHT;
		}
		else if (next.x < prev.x)
		{
			direction = DOWN_LEFT;
		}
		else
		{
			direction = DOWN;
		}
	}
	// down
	else if (next.y < prev.y)
	{
		if (next.x > prev.x)
		{
			direction = UP_RIGHT;
		}
		else if (next.x < prev.x)
		{
			direction = UP_LEFT;
		}
		else
		{
			direction = UP;
		}
	}
	// sides
	else
	{
		if (next.x > prev.x)
		{
			direction = RIGHT;
		}
		else
		{
			direction = LEFT;
		}
	}

	return direction;
}

double Manager::CalcDelta(Location prev, Location next)
{
	int nextDirection = this->CalcNextStep(prev,next);
	double nextAngle;
	switch (nextDirection)
	{
	case UP:
		nextAngle = ANGLE_UP;
		break;
	case DOWN:
		nextAngle = ANGLE_DOWN;
		break;
	case RIGHT:
		nextAngle = ANGLE_RIGHT;
		break;
	case LEFT:
		nextAngle = ANGLE_LEFT;
		break;
	case UP_LEFT:
		nextAngle = ANGLE_UP_LEFT;
		break;
	case UP_RIGHT:
		nextAngle = ANGLE_UP_RIGHT;
		break;
	case DOWN_LEFT:
		nextAngle = ANGLE_DOWN_LEFT;
		break;
	case DOWN_RIGHT:
		nextAngle = ANGLE_DOWN_RIGHT;
		break;
	default:
		return -1;
	}

	this->_robot->Read();
	double deltaAngle = nextAngle - this->_robot->getYaw();

	return (deltaAngle);
}

Manager::~Manager() {
}
