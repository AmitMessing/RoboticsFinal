#include <iostream>
#include <libplayerc++/playerc++.h>
#include "SLAM/Map.h"
#include "Manager.h"
#include "Plans/AvoidObstaclesPlan.h"
#include "Png/PngUtil.h"
#include "ConfigurationManager.h"
#include "WayPointsManager.h"

using namespace std;
using namespace PlayerCc;

int main()
{
	cout << "Started Running Robot" << endl;

	Map map = Map();
	vector<Point> path = map.GetAStartPath();
	WayPointsManager waypointManager = WayPointsManager();
	vector<Location> waypoints = waypointManager.GetWayPoints(&path);

	Robot robot("localhost",6665);
//	AvoidObstaclesPlan plan(&robot);
	Manager manager(&robot, waypoints);
	manager.run();
	return 0;
}
