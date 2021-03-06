
#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <vector>
#include "Constants.h"

using namespace std;

class WayPointsManager {
public:
	WayPointsManager();
	virtual ~WayPointsManager();
	vector<Location> GetWayPoints(vector<Point>* path);

private:
	vector<Point> _path;
	unsigned _currPoint;
	int _prevDirection;
	int GetNextDirection();
	Location GetLocation(Point point);
};

#endif /* WAYPOINTSMANAGER_H_ */
