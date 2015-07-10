#include "Behavior.h"

class MoveForward : public Behavior {
public:
	MoveForward(Robot* robot) : Behavior(robot) {}
	virtual ~MoveForward();
	void action();
	bool startCond();
	bool stopCond();
	double availableSpace();
};
