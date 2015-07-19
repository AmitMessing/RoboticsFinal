#include <fstream>
#include <iostream>
#include <math.h>
#include "Map.h"
#include "../Png/lodepng.h"

using namespace std;

Map::Map()
{
	this->_width = 0;
	this->_height = 0;

	this->LoadMap();
	this->_gridResolution = ConfigurationManager::GetGridRosolution();

	this->_gridHeight = (int)(this->_height / this->_gridResolution ) + 1;
	this->_gridWidth = (int)(this->_width / this->_gridResolution ) + 1;


	this->_grid = new int*[this->_gridHeight];

	for (int row = 0; row < this->_gridHeight; row++){
		this->_grid[row] = new int[this->_gridWidth];
		for (int col = 0; col < this->_gridWidth; col++){
			this->_grid[row][col] = FREE_CELL;
		}
	}

	this->BlowMap(ConfigurationManager::GetBlowFactor());
}


Map::~Map()
{
}

void Map::LoadMap(){
	unsigned error = lodepng::decode(this->_image,this->_width, this->_height, ConfigurationManager::GetMapFilePath());
	if (error){
		cout << "LoadMap->decode returned an error:" << error << " , " << lodepng_error_text(error);
	}
}

void Map::BlowMap(int blowFactor){
	vector<unsigned char> blowedMap;
	for (int index = 0; index < this->_image.size(); index++){
		blowedMap.push_back(this->_image[index]);
	}

	for (int row = 0; row < this->_height; row++){
		for (int col = 0; col < this->_width; col++){
			if (this->_image[this->GetPositionInMapVector(this->_width,row,col)] == 0){
				for (int bf = 1; bf < blowFactor + 1; bf++)
				{
					// left
					if (((int)col - bf) >= 0)
					{
						blowedMap[this->GetPositionInMapVector(this->_width,row,col - bf) + 0] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row,col - bf) + 1] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row,col - bf) + 2] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row,col - bf) + 3] = 255;
					}
					// right
					if (col + bf < this->_width)
					{
						blowedMap[this->GetPositionInMapVector(this->_width,row,col + bf) + 0] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row,col + bf) + 1] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row,col + bf) + 2] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row,col + bf) + 3] = 255;
					}
					// up
					if (((int)row - bf) >= 0)
					{
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col) + 0] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col) + 1] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col) + 2] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col) + 3] = 255;
					}
					// down
					if (row + bf < this->_height)
					{
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col) + 0] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col) + 1] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col) + 2] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col) + 3] = 255;
					}
					// diagonal up-right
					if((row + bf <  this->_height) && (col + bf < this->_width))
					{
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col + bf) + 0] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col + bf) + 1] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col + bf) + 2] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col + bf) + 3] = 255;
					}
					// diagonal up-left
					if((row + bf <  this->_height) && ((col - bf) >= 0))
					{
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col - bf) + 0] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col - bf) + 1] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col - bf) + 2] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row + bf,col - bf) + 3] = 255;
					}

					// diagonal down-right
					if(((row - bf) >= 0) && (col + bf <  this->_width))
					{
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col + bf) + 0] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col + bf) + 1] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col + bf) + 2] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col + bf) + 3] = 255;
					}
					// diagonal down-left
					if(((row - bf) >= 0) && ((col - bf) >= 0))
					{
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col - bf) + 0] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col - bf) + 1] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col - bf) + 2] = 0;
						blowedMap[this->GetPositionInMapVector(this->_width,row - bf,col - bf) + 3] = 255;
					}
				}
			}
		}
	}
	this->_blowedMap = blowedMap;

	lodepng::encode("/home/colman/Desktop/blowedMap.png", this->_blowedMap, this->_width, this->_height);

	for (int row = 0; row < this->_height; row++){
		for (int col = 0; col < this->_width; col++){
			if (this->_image[this->GetPositionInMapVector(this->_width,row,col)] == 0){
				this->_grid[(int)(row / this->_gridResolution)][(int)(col / this->_gridResolution)] = OCCUPIED_CELL;
			}
		}

	}

	PathPlanner pp = PathPlanner(this->_grid, this->_gridHeight, this->_gridWidth);
	Point startLoc = Point(
			ConfigurationManager::GetStartLocation().x,
			ConfigurationManager::GetStartLocation().y);
	vector<Point> path = pp.AStar(startLoc,ConfigurationManager::GetGoal());

	for (unsigned int index = 0; index < path.size(); index++){
		this->_grid[path[index].y][path[index].x] = PATH_CELL;
	}

	this->PrintMap();
}

unsigned int Map::GetPositionInMapVector(unsigned width, unsigned row, unsigned col){
	return ((width * row * ConfigurationManager::GetResolutionRatio()) + col * ConfigurationManager::GetResolutionRatio());
}

void Map::PrintMap(){
	for (int row = 0; row < this->_gridHeight; row++)
	{
		for (int col = 0; col < this->_gridWidth; col++){
			cout << (char)this->_grid[row][col];
		}
		cout << endl;
	}
}


/*void Map::PrintMap()
{
	cout << "Printing Grid: " << endl;
	cout << "--\t";
	for (int j = 0; j < this->_gridWidth ; j++)
	{
		if (j % 5 == 0)
		{
			cout << "|";
		}
		else
		{
			cout << "-";
		}
	}
	cout << endl;
	for (int i = 0; i < this->_gridHeight ; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < this->_gridWidth ; j++)
		{
			switch(this->_grid[i][j])
			{
			case FREE_CELL:
				cout << " ";
				break;
			case OCCUPIED_CELL:
				cout << "*";
				break;
			//case PATH_CELL:
			//	cout << "o";
			//	break;
			//case START_CELL:
			//	cout << "s";
			//	break;
			//case GOAL_CELL:
			//	cout << "g";
			//	break;
			}
		}
		cout << endl;
	}*/
//}

