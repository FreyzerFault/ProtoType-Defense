#pragma once
#include "Map/Path.h"

class Wave
{
public:
	Wave() = delete; // Can't exists a Wave without a Path
	
	Wave(Path& path, int numWave = 0, TypeEnemy type = TypeEnemy::basic, int numEnemies = 5, float delay = 3, float frecuency = 1);

	void startWave() const;
	void endWave();
	void sendEnemy() const;
	void sendEnemy(float deltaTime);

	float getDelay() const { return delay; }
	float getFrecuency() const { return frecuency; }

	bool isEnded() const { return ended; }

	std::string toString() const;

private:
	Path* path;
	
	int numEnemies;
	int enemiesLeft;
	
	TypeEnemy type;
	
	float delay; // Seconds until First Enemy is sent
	float frecuency; // enemies / second

	int numWave;

	float enemyTimer = 0;
	float delayTimer = 0;

	bool ended = false;

};

