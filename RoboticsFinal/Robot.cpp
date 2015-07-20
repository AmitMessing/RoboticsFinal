#include "Robot.h"
#include "math.h"

using namespace std;

double Robot::getLaserScan(int index)
{
	return _lp[index];
}

void Robot::Read()
{
	_pc.Read();
}

void Robot::setSpeed(double forwardSpeed, double rotationSpeed)
{
	_pp.SetSpeed(forwardSpeed,rotationSpeed);
}

double Robot::getXPos()
{
	return _pp.GetXPos();
}

double Robot::getYPos()
{
	return _pp.GetYPos();
}

double Robot::getYaw()
{
	return _pp.GetYaw();
}

Location Robot::GetLocation(){
	return Location(_pp.GetXPos(), _pp.GetYPos(), _pp.GetYaw() * 180 / M_PI);
}

Robot::~Robot()
{
	delete &_pc;
	delete &_pp;
	delete &_lp;
}
