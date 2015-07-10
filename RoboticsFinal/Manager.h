#ifndef MANAGER_H_
#define MANAGER_H_
#include "Plans/Plan.h"
#include "Behaviors/Behavior.h"
#include "Robot.h"
#include "SLAM/SlamManager.h"

// Noise to simulate real world wrong reads.
#define NOISE_POSITION_FACTOR 0.02
#define NOISE_YAW_FACTOR 0.01

class Manager {
	Robot* _robot;
	Plan* _plan;
	Behavior* _currBehavior;
	SlamManager _slamManager;
public:
	Manager(Robot* robot, Plan* plan);
	virtual ~Manager();
	void run();
};

#endif /* MANAGER_H_ */
