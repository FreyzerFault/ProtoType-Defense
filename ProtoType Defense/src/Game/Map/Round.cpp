#include "Round.h"

static int numWaves = 2;
static int baseReward = 100;

Round::Round(Path& path)
{
	for (int i = 0; i < numWaves; ++i)
	{
		waves.emplace_back(path, basic, 5, 5, 1);
	}
}


void Round::startRound()
{
	currentWave = &waves.front();
	std::cout << "Waves: " << numWaves << std::endl;
	std::cout << "Wave " << numWaves - waves.size() + 1 << " started" << std::endl;
}

void Round::sendWave()
{
	currentWave->startWave();

	waves.pop_front();
	if (!waves.empty())
	{
		currentWave = &waves.front();
		std::cout << "Wave " << numWaves - waves.size() + 1 << " started" << std::endl;
		return;
	}
	std::cout << "Round completed" << std::endl;
	std::cout << "Reward: " << getReward() << "$" << std::endl;
}

void Round::sendEnemy() const
{
	currentWave->sendEnemy();
}

int Round::getReward()
{
	return baseReward;
}

