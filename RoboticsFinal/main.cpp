#include <iostream>
#include <libplayerc++/playerc++.h>
#include "SLAM/Map.h"
#include "Manager.h"
#include "Plans/AvoidObstaclesPlan.h"

using namespace std;
using namespace PlayerCc;

int main()
{
	Robot robot("localhost",6665);
	AvoidObstaclesPlan plan(&robot);
	Manager manager(&robot, &plan);
	manager.run();
	return 0;
}
