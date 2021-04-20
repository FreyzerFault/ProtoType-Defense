#pragma once
#include "Map/Path.h"

class Wave
{
public:
	Wave(Path& path);
	Wave(Path& path, TypeEnemy type, int numEnemies, float delay, float frecuency);

	void startWave() const;
	void sendEnemy();

	float getDelay() const { return delay; }
	float getFrecuency() const { return frecuency; }

private:
	Path* path;
	
	int numEnemies;
	int enemiesLeft;
	
	TypeEnemy type;
	
	float delay;
	float frecuency;

};

