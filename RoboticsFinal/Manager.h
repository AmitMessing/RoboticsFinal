
#ifndef MANAGER_H_
#define MANAGER_H_
#include "Robot.h"

class Manager {
	Robot* _robot;
	vector<Location> _wayPoints;
//	Behavior* _currBehavior;
public:
	Manager(Robot* robot,  vector<Location> wayPoints);
	void ChangeDirection(Location prev, Location next, bool startPoint);
	double CalcDelta(Location prev, Location next);
	int CalcNextStep(Location prev, Location next);
	double CalcDistance(Location prev, Location next);
	virtual ~Manager();
	void run();
};

#endif  MANAGER_H_
