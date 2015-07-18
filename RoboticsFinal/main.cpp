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

	Map map = Map();

//	Robot robot("localhost",6665);
//	AvoidObstaclesPlan plan(&robot);
//	Manager manager(&robot, &plan);
//	ConvertMapBlackToWhiteAndWhiteToBlack("/home/colman/Desktop/roboticLabMap.png");
//	manager.run();
	return 0;
}
