#pragma once
#include "pch.h"

#include "Map/Path.h"

class Wave
{
public:
	Wave() = delete; // Can't exists a Wave without a Path
	
	Wave(Path& path, int numWave = 0, TypeEnemy type = TypeEnemy::basic, int numEnemies = 5, float delay = 3, float frecuency = 1);

	void startWave() const;
	void endWave();
	
	bool isEnded() const { return ended; }

	float getDelay() const { return delay; }
	float getFrecuency() const { return frecuency; }

	void sendEnemy() const;
	void sendEnemy(float deltaTime);

	std::string toString() const;

private:
	Path* path;

	// Enemies
	int numEnemies;
	int enemiesLeft;
	
	TypeEnemy type;

	// Timing
	float delay; // Seconds until First Enemy is sent
	float frecuency; // enemies / second

	float enemyTimer = 0;
	float delayTimer = 0;

	bool ended = false;

	int numWave;


};

