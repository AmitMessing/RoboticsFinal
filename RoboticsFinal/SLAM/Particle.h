#ifndef PARTICLE_H_
#define PARTICLE_H_

#define DIS_THRESHOLD 1.0
#define YAW_ANGLE_THRESHOLD 2.1
#define NORMALIZE_FACTOR 2.0
#define NEW_PARTICLE_RADIUS 0.2
#define NEW_PARTICLE_ANGLE_LIMIT 60

#include "../Constants.h"
#include "Particle.h"
#include "../Robot.h"
#include "Map.h"

class Particle
{
private:
	Map* _map;
	double _xPos;
	double _yPos;
	double _yaw;
	double _belief;
	double calcNewLocationProbability(double deltaX, double deltaY, double deltaYaw);
	double calcObservationsAccuracy(Robot* robot);
	void freeCellsToObstacle(double obstacleXPos, double obstacleYPos, double distanceToObstacle);
	double laserIndexToLaserAngle(int index);

public:
	Particle(double x, double y, double pYaw, double bel, Map* map);
	virtual ~Particle();
	void update(double deltaX, double deltaY, double deltaYaw, Robot* robot);
	Particle* createNewParticle();
	Map* getMap();
	double getBelief();
};

#endif /* PARTICLE_H_ */
