/*
 * PathPlanner.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "PathPlanner.h"

PathPlanner::PathPlanner(int** grid, int gridHeigth, int gridWidth) {
	this->_grid = grid;
	this->_gridHeight = gridHeigth;
	this->_gridWidth = gridWidth;
}

PathPlanner::~PathPlanner() {

}

vector<Point> PathPlanner::AStar(Point start, Point goal){
	vector<Point> path;
	vector<Point> openset; // The set of tentative nodes to be evaluated.
	vector<Point> closedset; // The set of nodes already evaluated.

	Point* camefrom[this->_gridHeight]; // The map of navigated nodes.
	double* g_score[this->_gridHeight]; // Cost from start along best known path.
	double* f_score[this->_gridHeight]; // Estimated total cost from start to goal through y.

	for (int index = 0; index < this->_gridHeight; index++){
		camefrom[index] = new Point[this->_gridWidth];
		g_score[index] = new double[this->_gridWidth];
		f_score[index] = new double[this->_gridWidth];
	}

	camefrom[start.y][start.x] = start;
	openset.push_back(start);

	g_score[start.y][start.x] = 0;
	f_score[start.y][start.x] = g_score[start.y][start.x] + this->heuristic_cost_estimate(start,goal);

	while(!openset.empty()){
		int curIndex = getLowestScoreIndex(openset, f_score);
		Point current = openset[curIndex];

		if (current == goal){
			path = this->reconstruct_path(camefrom, goal);
			break;
		}

		openset.erase(openset.begin() + curIndex);
		closedset.push_back(current);

		queue<Point> neighbors = this->getNeighbors(current);

		while (!neighbors.empty()){
			Point neighbor = neighbors.front();
			neighbors.pop();

			if (std::find(closedset.begin(),closedset.end(), neighbor) != closedset.end()){
				continue;
			}

			double tentative_g_score = g_score[current.y][current.x] + 1;

			if(this->checkObstacleAround(current)){
				tentative_g_score += INT_MAX;
			}

			if (std::find(openset.begin(),openset.end(), neighbor) == openset.end() ||
				tentative_g_score < g_score[neighbor.y][neighbor.x])
			{
				camefrom[neighbor.y][neighbor.x] = current;
				g_score[neighbor.y][neighbor.x] = tentative_g_score;
				f_score[neighbor.y][neighbor.x] = tentative_g_score + this->heuristic_cost_estimate(neighbor,goal);

				if(std::find(openset.begin(),openset.end(), neighbor) == openset.end())
				{
					openset.push_back(neighbor);
				}
			}
		}
	}

	return path;
}

double PathPlanner::heuristic_cost_estimate(Point p1, Point p2){
	double lengthY = p1.y - p2.y;
	double lengthX = p1.x - p2.x;

	return (abs(lengthY) + abs(lengthX));
}

int PathPlanner::getLowestScoreIndex(vector<Point> points, double** scores){
	int lowestIndex = 0;
	Point lowestPoint = points[0];

	for (unsigned int index = 1; index < points.size(); index++){
		Point temp = points[index];
		if (scores[temp.y][temp.x] < scores[lowestPoint.y][lowestPoint.x]){
			lowestPoint = temp;
			lowestIndex = index;
		}
	}

	return lowestIndex;
}

vector<Point> PathPlanner::reconstruct_path(Point** camefrom, Point goal){
	vector<Point> path;

	Point current = goal;
	Point pointCamefrom = camefrom[current.y][current.x];
	path.insert(path.begin(), current);

	while(current != pointCamefrom){
		path.insert(path.begin(), pointCamefrom);
		current = pointCamefrom;
		pointCamefrom = camefrom[current.y][current.x];
	}

	return path;
}

queue<Point> PathPlanner::getNeighbors(Point point)
{
	queue<Point> neighbors;
	int row = point.y;
	int col = point.x;

	// left
	if (col - 1 > 0)
	{
		if (this->_grid[row][col - 1] == FREE_CELL)
		{
			neighbors.push(Point(row,col - 1));
		}
	}
	//right
	if (col + 1 < this->_gridWidth)
	{
		if (this->_grid[row][col + 1] == FREE_CELL)
		{
			neighbors.push(Point(row,col + 1));
		}
	}
	//up
	if (row - 1 > 0)
	{
		if (this->_grid[row - 1][col] == FREE_CELL)
		{
			neighbors.push(Point(row - 1,col));
		}
	}
	//down
	if (row + 1 < this->_gridHeight)
	{
		if (this->_grid[row + 1][col] == FREE_CELL)
		{
			neighbors.push(Point(row + 1,col));
		}
	}
	//up-left
	if ((row - 1 > 0) && (col - 1 > 0))
	{
		if (this->_grid[row - 1][col - 1] == FREE_CELL)
		{
			neighbors.push(Point(row - 1,col - 1));
		}
	}
	//up-right
	if ((row - 1 > 0) && (col + 1 < this->_gridWidth))
	{
		if (this->_grid[row - 1][col - 1] == FREE_CELL)
		{
			neighbors.push(Point(row - 1,col - 1));
		}
	}
	//down-left
	if ((row + 1 < this->_gridHeight) && (col - 1 > 0))
	{
		if (this->_grid[row - 1][col - 1] == FREE_CELL)
		{
			neighbors.push(Point(row - 1,col - 1));
		}
	}
	//down-right
	if ((row + 1 < this->_gridHeight) && (col + 1 < this->_gridWidth))
	{
		if (this->_grid[row - 1][col - 1] == FREE_CELL)
		{
			neighbors.push(Point(row - 1,col - 1));
		}
	}

	return neighbors;
}

bool PathPlanner::checkObstacleAround(Point point)
{
	int row = point.y;
	int col = point.x;
	bool obstacle = false;

	//left
	if (col - 1 > 0)
	{
		if (this->_grid[row][col - 1] == OCCUPIED_CELL)
		{
			obstacle = true;
		}
	}
	//right
	if (col + 1 < this->_gridWidth)
	{
		if (this->_grid[row][col + 1] == OCCUPIED_CELL)
		{
			obstacle = true;
		}
	}
	//up
	if (row - 1 > 0)
	{
		if (this->_grid[row - 1][col] == OCCUPIED_CELL)
		{
			obstacle = true;
		}
	}
	//down
	if (row + 1 < this->_gridHeight)
	{
		if (this->_grid[row + 1][col] == OCCUPIED_CELL)
		{
			obstacle = true;
		}
	}
	//up-left
	if ((row - 1 > 0) && (col - 1 > 0))
	{
		if (this->_grid[row - 1][col - 1] == OCCUPIED_CELL)
		{
			obstacle = true;
		}
	}
	//up-right
	if ((row - 1 > 0) && (col + 1 < this->_gridWidth))
	{
		if (this->_grid[row - 1][col + 1] == OCCUPIED_CELL)
		{
			obstacle = true;
		}
	}
	//down-left
	if ((row + 1 < this->_gridHeight) && (col - 1 > 0))
	{
		if (this->_grid[row + 1][col - 1] == OCCUPIED_CELL)
		{
			obstacle = true;
		}
	}
	//down-right
	if ((row + 1 < this->_gridHeight) && (col + 1 < this->_gridWidth))
	{
		if (this->_grid[row + 1][col + 1] == OCCUPIED_CELL)
		{
			obstacle = true;
		}
	}

	return obstacle;
}
