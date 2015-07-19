#ifndef LOCALIZATATIONMANAGER_H_
#define LOCALIZATATIONMANAGER_H_

#define BELIEF_MIN_THRESHOLD 0.25
#define BELIEF_MAX_THRESHOLD 0.8
#define MAX_PARTICLES_NUM 40

#include "Particle.h"
#include "Robot.h"

using namespace std;

class LocalizationManager {
private:
	Particle* _particles[MAX_PARTICLES_NUM];
	int _numOfParticles;
	Robot* _robot;
	bool addParticle(Particle* par);
	bool deleteParticle(int index);
public:
	LocalizationManager(Robot* robot): _robot(robot), _numOfParticles(0){};
	virtual ~LocalizationManager();
	void update(double deltaX, double deltaY, double deltaYaw);
};

#endif /* LOCALIZATATIONMANAGER_H_ */
