#include "Wave.h"


Wave::Wave(Path& path)
	: path(&path), numEnemies(5), enemiesLeft(numEnemies), type(basic), delay(2), frecuency(2)
{
}

Wave::Wave(Path& path, TypeEnemy type, int numEnemies, float delay, float frecuency)
	: path(&path), numEnemies(numEnemies), enemiesLeft(numEnemies), type(type), delay(delay), frecuency(frecuency)
{
}

void Wave::startWave() const
{
	std::cout << "Starting wave [Enemy Type: " << type << " x" << numEnemies << "]" << std::endl;
}

void Wave::sendEnemy()
{
	if(enemiesLeft > 0)
	{
		path->spawnEnemy(type);
		enemiesLeft--;
	}
}
