#ifndef MAP_H_
#define MAP_H_

#define MAP_SIZE 200
#define RESOLUTION 0.27

#include "../Constants.h"

class Map {
private:
	int getColFromXPos(double x);
	int getRowFromYPos(double y);
	char _mapMatrix[MAP_SIZE][MAP_SIZE];
public:
	Map();
	virtual ~Map();
	Map(Map* mapToCopy);
	void setMapValue(double x, double y, char value);
	void printMap();
	char getMapValueFromRealLocation(double x, double y);
	void CreateMap(char* filePath);
};

#endif
