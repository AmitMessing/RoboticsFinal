#ifndef PLAN_H_
#define PLAN_H_

#include "../Behaviors/Behavior.h"

class Plan
{
protected:
	Behavior** _behaviorsArr;
	Robot* _robot;
	Behavior* _startBehavior;

public:
	Plan(Robot* robot);
	virtual Behavior* startBehavior()=0;
	virtual ~Plan();
};

#endif /* PLAN_H_ */
