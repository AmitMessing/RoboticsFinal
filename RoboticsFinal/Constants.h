#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <iostream>

using namespace std;

#define FREE_CELL ' '
#define OCCUPIED_CELL '*'
#define UNKNOWN_CELL '?'
#define PATH_CELL '@'
#define MAX_LASER_INDEX 665

// robot movement directions
#define MOVE_FORWARD 0
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define UP_LEFT 5
#define UP_RIGHT 6
#define DOWN_LEFT 7
#define DOWN_RIGHT 8
#define STOP 9

// movement
#define FORWARD_SPEED_SLOW 0.2
#define FORWARD_SPEED 0.4
#define TOLERANCE_DISTANCE 1.75

// robot angle directions
#define ANGLE_UP 1.57
#define ANGLE_DOWN -1.57
#define ANGLE_RIGHT 0
#define ANGLE_LEFT -3.14
#define ANGLE_UP_LEFT 2.425
#define ANGLE_UP_RIGHT 0.785
#define ANGLE_DOWN_LEFT -2.356
#define ANGLE_DOWN_RIGHT -0.785

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

	bool isEqual(const Point& point) const {
		return ((this->x == point.x) && (this->y == point.y));
	}
};

class Location {

public:
	float x;
	float y;
	float yaw;

    Location(){
    		this->x = 0;
    		this->y = 0;
    		this->yaw = 0;
    	}

    Location(float x, float y, float yaw){
    		this->x = x;
    		this->y = y;
    		this->yaw = yaw;
    	}


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

#endif /* CONSTANTS_H_ */
