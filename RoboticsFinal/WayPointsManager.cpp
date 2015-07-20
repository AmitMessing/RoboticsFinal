

#include "WayPointsManager.h"
#include <vector>
#include "Constants.h"
#include "ConfigurationManager.h"

using namespace std;

WayPointsManager::WayPointsManager() {
	this->_currPoint = 0;
	this->_prevDirection = MOVE_FORWARD;
}

WayPointsManager::~WayPointsManager() {

}

vector<Location> WayPointsManager::GetWayPoints(vector<Point>* path){
	this->_path = path[0];
	vector<Location> result;

	int direction = GetNextDirection();

	while(direction != STOP)
	{
		if (direction != MOVE_FORWARD)
		{
			Point p = this->_path[this->_currPoint - 1];
			result.push_back(this->GetLocation(p));
		}

		direction = GetNextDirection();
	}

	result.push_back(this->GetLocation(this->_path[this->_currPoint - 1]));

	return result;
}

Location WayPointsManager::GetLocation(Point point)
{
	double temp = ((550 / (ConfigurationManager::GetGridRosolution() * ConfigurationManager::GetResolutionRatio()))/2);
	double x =  (point.x / (ConfigurationManager::GetGridRosolution())) - temp;
	double y =  (point.y / (ConfigurationManager::GetGridRosolution() * ConfigurationManager::GetResolutionRatio())) - temp;

	return Location(x,y,0);
}

int WayPointsManager::GetNextDirection()
{
	int toReturn;
	this->_currPoint++;

	if (this->_currPoint != this->_path.size())
	{
		Point prev = this->_path[this->_currPoint - 1];
		Point next = this->_path[this->_currPoint];

		if (prev.y == next.y)
		{
			if(prev.x > next.x)
			{
				toReturn = LEFT;
			}
			else if(prev.x < next.x)
			{
				toReturn = RIGHT;
			}
		}
		else if (prev.x  == next.x)
		{
			if (prev.y > next.y)
			{
				toReturn = UP;
			}
			else if (prev.y < next.y)
			{
				toReturn = DOWN;
			}
		}
		else
		{
			if(prev.y > next.y)
			{
				if (prev.x > next.x)
				{
					toReturn = UP_LEFT;
				}
				else
				{
					toReturn = UP_RIGHT;
				}
			}
			else
			{
				if (prev.x > next.x)
				{
					toReturn = DOWN_LEFT;
				}
				else
				{
					toReturn = DOWN_RIGHT;
				}
			}
		}

		if (toReturn == this->_prevDirection)
		{
			toReturn = MOVE_FORWARD;
		}
		else
		{
			this->_prevDirection = toReturn;
		}
	}
	else
	{
		toReturn = STOP;
	}

	return toReturn;
}



