#include "LocalizationManager.h"

using namespace std;

void LocalizationManager::update(double deltaX, double deltaY, double deltaYaw)
{
	double bestBelief = 0;
	Particle* bestParticle;

	// Create a particle if there are no particles
	if (_numOfParticles == 0)
	{
		addParticle(new Particle(0,0,0,1,new Map()));
	}

	int toCreate[_numOfParticles];
	int toDelete[_numOfParticles];
	int toCreateCount = 0, toDeleteCount = 0;

	// Update the particles according to the robot's scans
	for (int i = 0; i < _numOfParticles; i++)
	{
		_particles[i]->update(deltaX, deltaY, deltaYaw, _robot);

		double currBelief = _particles[i]->getBelief();

		// Delete the particle if it's belief is too low
		if (currBelief < BELIEF_MIN_THRESHOLD)
		{
			toDelete[toDeleteCount] = i;
			toDeleteCount++;
		}
		else
		{
			// Create new particles if the belief is high
			if ((currBelief > BELIEF_MAX_THRESHOLD))
			{
				toCreate[toCreateCount] = i;
				toCreateCount++;
			}

			// Update the best particle
			if (bestBelief < currBelief)
			{
				bestBelief = currBelief;
				bestParticle = _particles[i];
			}
		}
	}

	for (int i = 0; i < toDeleteCount; i++)
	{
		deleteParticle(toDelete[i]);
	}

	for (int i = 0; i < toCreateCount; i++)
	{
		for	(int j = 1; j <= 3; j++)
		{
			if (_numOfParticles < MAX_PARTICLES_NUM)
			{
				addParticle(_particles[toCreate[i]]->createNewParticle());
			}
		}
	}

	// Print the best particle's map
	bestParticle->getMap()->printMap();
}

bool LocalizationManager::addParticle(Particle* particle)
{
	if (_numOfParticles < MAX_PARTICLES_NUM)
	{
		_particles[_numOfParticles] = particle;
		_numOfParticles++;
		return true;
	}

	return false;
}

bool LocalizationManager::deleteParticle(int index)
{
	if (_numOfParticles > 0)
	{
		_particles[index] = _particles[_numOfParticles - 1];
		_particles[_numOfParticles - 1] = NULL;
		_numOfParticles--;
		return true;
	}

	return false;
}

LocalizationManager::~LocalizationManager() {
	delete[] _particles;
}
