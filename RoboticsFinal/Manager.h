
#ifndef MANAGER_H_
#define MANAGER_H_
#include "Behaviors/Behavior.h"
#include "Robot.h"
#include "LocalizationManager.h"

// Noise to simulate real world wrong reads.
#define NOISE_POSITION_FACTOR 0.02
#define NOISE_YAW_FACTOR 0.01

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
