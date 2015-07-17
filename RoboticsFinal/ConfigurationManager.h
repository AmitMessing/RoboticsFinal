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
	static const double GetCentimetersPerPixel();
	static const int GetGridCentimetersSize();
	static const Location GetStartLocation();
	static const Point GetEndLocation();
	static const double GetRobotSize();

private:
	ConfigurationManager();
	static const char* map_file_path_;
		static const double centimeters_per_pixel_ = 2.5;
		static const int grid_centimeters_size_ = 10;
		static const Location start_location_;
		static const Point end_location_;
		static const double robot_size =  30.0;
		static const int cells_per_waypoint_ = 5;
};

inline const Location ConfigurationManager::GetStartLocation() {
	return start_location_;
}

inline const Point ConfigurationManager::GetEndLocation() {
	return end_location_;
}

inline const char* ConfigurationManager::GetMapFilePath() {
	return map_file_path_;
}

#endif /* CONFIGURATIONMANAGER_H_ */
