#pragma once
#include "pch.h"

#include "Map/Path.h"

class Wave
{
public:
	Wave() = delete; // Can't exists a Wave without a Path
	
	Wave(Path& path, int numWave = 0, TypeEnemy type = TypeEnemy::basic, int numEnemies = 5, GLfloat delay = 3, GLfloat frecuency = 1);

	void startWave() const;
	void endWave();
	
	bool isEnded() const { return ended; }

	GLfloat getDelay() const { return delay; }
	GLfloat getFrecuency() const { return frecuency; }

	void sendEnemy() const;
	void sendEnemy(GLfloat deltaTime);

	std::string toString() const;

private:
	Path* path;

	// Enemies
	int numEnemies;
	int enemiesLeft;
	
	TypeEnemy type;

	// Timing
	GLfloat delay; // Seconds until First Enemy is sent
	GLfloat frecuency; // enemies / second

	GLfloat enemyTimer = 0;
	GLfloat delayTimer = 0;

	bool ended = false;

	int numWave;


};

