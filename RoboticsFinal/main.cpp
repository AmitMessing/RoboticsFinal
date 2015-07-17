#include <iostream>
#include <libplayerc++/playerc++.h>
#include "SLAM/Map.h"
#include "Manager.h"
#include "Plans/AvoidObstaclesPlan.h"
#include "Png/PngUtil.h"
#include "ConfigurationManager.h"

using namespace std;
using namespace PlayerCc;

int main()
{
	cout << "Started Running Robot" << endl;

	const char* filePath = ConfigurationManager::GetMapFilePath();
	const Location start_location = ConfigurationManager::GetStartLocation();
	const Point end_location = ConfigurationManager::GetEndLocation();
	Map::CreateMap(filePath);

//	Robot robot("localhost",6665);
//	AvoidObstaclesPlan plan(&robot);
//	Manager manager(&robot, &plan);
//	ConvertMapBlackToWhiteAndWhiteToBlack("/home/colman/Desktop/roboticLabMap.png");
//	manager.run();
	return 0;
}
