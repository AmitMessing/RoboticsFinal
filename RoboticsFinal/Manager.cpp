//#include "Manager.h"
//#include <math.h>
//
//Manager::Manager(Robot* robot, Plan* plan) : _localizationManager(robot)
//{
//	_robot = robot;
//	_plan = plan;
//	_currBehavior = _plan->startBehavior();
//}
//
//void Manager::run()
//{
//	for(int i = 0; i< 5; i++)
//	{
//		_robot->Read();
//	}
//
//	double prevX = 0, prevY = 0, prevYaw = 0;
//	double newX, newY, newYaw;
//
//	while (_currBehavior != NULL)
//	{
//		while(!_currBehavior->stopCond())
//		{
//			_currBehavior->action();
//			_robot->Read();
//
//			// Get the robot's new location
//			newX = _robot->getXPos();
//			newY = _robot->getYPos();
//			newYaw = _robot->getYaw();
//
//			// Use some noise to simulate real world wrong reads.
//			newX = newX + ((double) rand() / (RAND_MAX)) * 2 * NOISE_POSITION_FACTOR - NOISE_POSITION_FACTOR;
//			newY = newY + ((double) rand() / (RAND_MAX)) * 2 * NOISE_POSITION_FACTOR - NOISE_POSITION_FACTOR;
//			newYaw = newYaw + ((double) rand() / (RAND_MAX)) * 2 * NOISE_YAW_FACTOR - NOISE_YAW_FACTOR;
//
//			cout << "Robot's position: " << newX << ", " << newY << ", " << newYaw << endl;
//
//			// Update particles and printing the map
//			_localizationManager.update(newX - prevX, newY - prevY, newYaw - prevYaw);
//
//			prevX = newX;
//			prevY = newY;
//			prevYaw = newYaw;
//		}
//
//		_currBehavior = _currBehavior->selectNextBehavior();
//	}
//}
//
//Manager::~Manager() {
//}
