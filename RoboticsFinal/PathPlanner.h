/*
 * PathPlanner.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include "Constants.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

class PathPlanner {
public:
	PathPlanner(int** grid, int gridHeigth, int gridWidth);
	virtual ~PathPlanner();
	vector<Point> AStar(Point start, Point goal);
	double heuristic_cost_estimate(Point p1, Point p2);
	int getLowestScoreIndex(vector<Point> points, double** scores);
	vector<Point> reconstruct_path(Point** camefrom, Point goal);
	queue<Point> getNeighbors(Point point);
	bool checkObstacleAround(Point point);
private:
	int** _grid;
	int _gridHeight, _gridWidth;
};

#endif /* PATHPLANNER_H_ */
