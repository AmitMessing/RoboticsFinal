/*
 * WayPointsManager.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: colman
 */

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
	// TODO Auto-generated destructor stub
}

vector<Location> WayPointsManager::GetWayPoints(vector<Point> path){

	this->_path = path;
	vector<Location> result;

	int direction = GetNextDirection();

		while(direction != STOP)
		{
			if (direction != MOVE_FORWARD)
			{
				result.push_back(this->GetRealLocation(this->_path[this->_currPoint - 1]));
			}

			direction = GetNextDirection();
		}

		result.push_back(this->GetRealLocation(this->_path[this->_currPoint - 1]));

		return result;
}

Location WayPointsManager::GetRealLocation(Point point)
{
	double gridResolution = ConfigurationManager::GetGridRosolution();
	double y = point.y / gridResolution + 100 * gridResolution / 2;
	double x = point.x / gridResolution + 100 * gridResolution / 2;

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


