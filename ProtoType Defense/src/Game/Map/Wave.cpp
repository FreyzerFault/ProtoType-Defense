#include "pch.h"
#include "Wave.h"

Wave::Wave(Path& path, int numWave, TypeEnemy type, int numEnemies, float delay, float frecuency)
	: path(&path), numEnemies(numEnemies), enemiesLeft(numEnemies), type(type), delay(delay), frecuency(frecuency), numWave(numWave)
{
}

void Wave::startWave() const
{
	std::cout << toString() << std::endl;
}

void Wave::endWave()
{
	ended = true;
}


void Wave::sendEnemy() const
{
	path->spawnEnemy(type);
}

void Wave::sendEnemy(float deltaTime)
{
	if (enemiesLeft > 0)
	{
		enemyTimer += deltaTime;
		if (enemyTimer >= 1 / frecuency) // If timer has reached the period that an enemy needs:
		{
			sendEnemy();
			enemiesLeft--;

			enemyTimer -= 1 / frecuency; // Reset Timer
		}
	}
	else // When all the enemies have been sent:
	{
		delayTimer += deltaTime;
		if (delayTimer >= delay)	// Wait a delay
		{
			endWave();
		}
	}
}

std::string Wave::toString() const
{
	std::stringstream ss;
	ss << "    Wave " << numWave << " [ " << numEnemies << " " << typeToString(const_cast<TypeEnemy&>(type)) << " - " << frecuency << "/sec ]";
	return ss.str();
}
