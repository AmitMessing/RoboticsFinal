#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <iostream>

using namespace std;

#define FREE_CELL ' '
#define OCCUPIED_CELL '*'
#define UNKNOWN_CELL '?'
#define MAX_LASER_INDEX 665

struct Point {
	unsigned int x_; // Rows = Heights
	unsigned int y_; // Cols = Width

	bool operator==(const Point& rhs) const {
		return ((this->x_ == rhs.x_) && (this->y_ == rhs.y_));
	}

	bool operator!=(const Point& rhs) const {
		return (!(this->operator ==(rhs)));
	}


	bool operator<(const Point& rhs) const {
		return ((this->x_ < rhs.x_) || ((this->x_ == rhs.x_) && (this->y_ < rhs.y_)));
	}

  void Print()
  {
      cout << "X:" << this->x_ << " Y:" << this->y_ << endl;
  }
};

struct Location {
	float x_;
        float y_;
        float yaw_;

         void Print()
        {
            cout << "X:" << this->x_ << " Y:" << this->y_ << " YAW:" << this->yaw_ << endl;
        }


    inline Location operator+(Location a) {
        return {a.x_+x_,a.y_+y_, a.yaw_ + yaw_};
    }

    inline Location operator-(Location a) {
            return {a.x_ - x_,a.y_ - y_, a.yaw_ - yaw_};
        }


    inline Location operator/(float a) {
        return {x_/a,y_/a,yaw_/a};
    }

    inline bool operator!=(Location a) {
           return (!((x_ == a.x_)&&(y_ == a.y_)&&(yaw_ == a.yaw_)));
       }

    inline void operator=(Location a) {
               x_ = a.x_;
               y_ = a.y_;
               yaw_ = a.yaw_;
           }

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

};

#endif /* CONSTANTS_H_ */
