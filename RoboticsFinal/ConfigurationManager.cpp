/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h"

const char* ConfigurationManager::map_file_path = "/home/colman/Desktop/roboticLabMap.png";
const double ConfigurationManager::MapResolutionCM = 2.5;
const double ConfigurationManager:: Grid_ResolutionCM = 10;
const Location ConfigurationManager::start_location = Location(362 , 305, 20);
const Point ConfigurationManager::goal = Point(169, 138);
const double ConfigurationManager::robot_size =  30.0;

ConfigurationManager::ConfigurationManager() {

}

ConfigurationManager::~ConfigurationManager() {
}

const char* ConfigurationManager::GetMapFilePath() {
	return map_file_path;
}

const double ConfigurationManager::GetMapResolution() {
	return MapResolutionCM;
}

const double ConfigurationManager::GetGridRosolution() {
	return Grid_ResolutionCM / MapResolutionCM;
}

const Location ConfigurationManager::GetStartLocation() {
	return start_location;
}

const Point ConfigurationManager::GetGoal() {
	return goal;
}

const double ConfigurationManager::GetRobotSize() {
	return robot_size;
}

const int ConfigurationManager::GetBlowFactor() {
	return (robot_size/2) + 1;
}

const int ConfigurationManager::GetResolutionRatio(){
	return (Grid_ResolutionCM / MapResolutionCM);
}
