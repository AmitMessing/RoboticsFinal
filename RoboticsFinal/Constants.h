#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <iostream>

using namespace std;

#define FREE_CELL ' '
#define OCCUPIED_CELL '*'
#define UNKNOWN_CELL '?'
#define MAX_LASER_INDEX 665

class Point {
public:
	unsigned int x; // Rows = Heights
	unsigned int y; // Cols = Width

	Point(){
		this->x = 0;
		this->y = 0;
	}

	Point(double x, double y){
		this->x = x;
		this->y = y;
	}

	bool operator==(const Point& rhs) const {
		return ((this->x == rhs.x) && (this->y == rhs.y));
	}

	bool operator!=(const Point& rhs) const {
		return (!(this->operator ==(rhs)));
	}


	bool operator<(const Point& rhs) const {
		return ((this->x < rhs.x) || ((this->x == rhs.x) && (this->y < rhs.y)));
	}

  void Print()
  {
      cout << "X:" << this->x << " Y:" << this->y << endl;
  }
};

struct Location {
	float x;
        float y;
        float yaw;

         void Print()
        {
            cout << "X:" << this->x << " Y:" << this->y << " YAW:" << this->yaw << endl;
        }


    inline Location operator+(Location a) {
        return {a.x + x, a.y + y, a.yaw + yaw};
    }

    inline Location operator-(Location a) {
            return {a.x - x,a.y - y, a.yaw - yaw};
        }


    inline Location operator/(float a) {
        return {x/a,y/a,yaw/a};
    }

    inline bool operator!=(Location a) {
           return (!((x == a.x)&&(y == a.y)&&(yaw == a.yaw)));
       }

    inline void operator=(Location a) {
               x = a.x;
               y = a.y;
               yaw = a.yaw;
           }

};

namespace GridCellState {
enum CellState {
	FREE,
	OBSTACLE,
	A_STAR_PATH,
	WAY_POINT,
	BLOWED
};
}

struct GridCell {
	GridCellState::CellState cell_state : 3;
	unsigned int cell_cost : 5;
};

#endif /* CONSTANTS_H_ */
