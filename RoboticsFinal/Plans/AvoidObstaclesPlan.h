#ifndef PLNOBSTACLEAVOID_H_
#define PLNOBSTACLEAVOID_H_

#include "Plan.h"
#include "../Behaviors/Behavior.h"
#include "../Behaviors/MoveForward.h"
#include "../Behaviors/TurnLeft.h"
#include "../Behaviors/TurnRight.h"

class AvoidObstaclesPlan: public Plan
{
public:
	AvoidObstaclesPlan(Robot* robot);
	Behavior* startBehavior();
	virtual ~AvoidObstaclesPlan();
};

#endif /* AVOIDOBSRACLESPLAN_H_ */
