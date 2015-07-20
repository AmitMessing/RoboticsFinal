#ifndef ROBOT_H_
#define ROBOT_H_
#include <iostream>
#include <libplayerc++/playerc++.h>
#include "Map.h"

using namespace std;
using namespace PlayerCc;

class Robot {
private:
	PlayerClient _pc;
	Position2dProxy _pp;
	LaserProxy _lp;

public:
	Robot(char* host, int port):_pc(host,port), _pp(&_pc),_lp(&_pc){
		//For fixing Player's reading BUG
		for(int i=0;i<15;i++){
			Read();
		}

		this->_pp.SetMotorEnable(true);
		this->_pp.SetOdometry(2.175, -2.875, (double)ConfigurationManager::GetStartLocation().yaw * M_PI / 180);
	}
	virtual ~Robot();
	double getLaserScan(int index);
	void Read();
	void setSpeed(double linearSpeed, double angularSpeed);
	double getXPos();
	double getYPos();
	double getYaw();
	Location GetLocation();
};

#endif /* ROBOT_H_ */
