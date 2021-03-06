#ifndef MAP_H_
#define MAP_H_

#include "ConfigurationManager.h"
#include "Constants.h"
#include <vector>
#include "PathPlanner.h"

using namespace std;

class Map {
private:
	int** _grid;
	vector<unsigned char> _image;
	vector<unsigned char> _blowedMap;
	unsigned _width, _height;
	int _gridWidth,_gridHeight;
	double _gridResolution;

public:
	Map();
	virtual ~Map();
	void LoadMap();
	void BlowMap(int blowFactor);
	unsigned int GetPositionInMapVector(unsigned width, unsigned row, unsigned col);
	void PrintMap();
	vector<Point> GetAStartPath();
	void SetMapValue(int x, int y, char value);
	char GetMapValue(int row, int col);
};

#endif
