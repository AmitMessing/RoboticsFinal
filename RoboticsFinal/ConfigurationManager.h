/*
 * ConfigurationManager.h
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include "Constants.h"

class ConfigurationManager {
public:
	virtual ~ConfigurationManager();
	static const char* GetMapFilePath();
	static const double GetMapResolution();
	static const double GetGridRosolution();
	static const Location GetStartLocation();
	static const Point GetGoal();
	static const double GetRobotSize();
	static const int GetBlowFactor();
	static const int GetResolutionRatio();

private:
	ConfigurationManager();
	static const char* map_file_path;
	static const double MapResolutionCM;
	static const double Grid_ResolutionCM ;
	static const Location start_location ;
	static const Point goal;
	static const double robot_size;
};

#endif /* CONFIGURATIONMANAGER_H_ */
