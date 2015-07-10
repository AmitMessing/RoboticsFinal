#include <fstream>
#include <iostream>
#include <math.h>
#include "Map.h"

using namespace std;

Map::Map()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			_mapMatrix[i][j] = UNKNOWN_CELL;
		}
	}
}

Map::Map(Map* mapToCopy)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			_mapMatrix[i][j] = mapToCopy->_mapMatrix[i][j];
		}
	}
}

void Map::setMapValue(double x, double y, char value)
{
	int col = getColFromXPos(x);
	int row = getRowFromYPos(y);

	if (_mapMatrix[row][col] != OCCUPIED_CELL)
	{
		_mapMatrix[row][col] = value;
	}
}

void Map::printMap()
{
	// Print to console
	for (int i=MAP_SIZE - 1; i >= 0 ; i--)
	{
		for (int j=MAP_SIZE - 1; j >= 0; j--)
		{
			cout << _mapMatrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

char Map::getMapValueFromRealLocation(double x, double y)
{
	int col = getColFromXPos(x);
	int row = getRowFromYPos(y);
	return _mapMatrix[row][col];
}

int Map::getColFromXPos(double x)
{
	return (x / RESOLUTION) + (MAP_SIZE / 2);
}

int Map::getRowFromYPos(double y)
{
	return (MAP_SIZE / 2) - (y / RESOLUTION);
}


