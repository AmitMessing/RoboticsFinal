#include "AvoidObstaclesPlan.h"

AvoidObstaclesPlan::AvoidObstaclesPlan(Robot* robot) : Plan(robot)
{
	_behaviorsArr = new Behavior*[3];

	// Create the behaviors
	_behaviorsArr[0] = new MoveForward(_robot);
	_behaviorsArr[1] = new TurnRight(_robot);
	_behaviorsArr[2] = new TurnLeft(_robot);

	// Set the possible next behaviors for each behavior
	_behaviorsArr[0]->addNextBehavior(_behaviorsArr[1]);
	_behaviorsArr[0]->addNextBehavior(_behaviorsArr[2]);
	_behaviorsArr[1]->addNextBehavior(_behaviorsArr[0]);
	_behaviorsArr[2]->addNextBehavior(_behaviorsArr[0]);

	_startBehavior = _behaviorsArr[0];
}

Behavior* AvoidObstaclesPlan::startBehavior()
{
	return _startBehavior;
}

AvoidObstaclesPlan::~AvoidObstaclesPlan() {
}
