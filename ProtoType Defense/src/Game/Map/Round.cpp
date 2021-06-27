#include "pch.h"
#include "Round.h"

static int numWaves = 2;

Round::Round()
	: Round(0)
{
}

Round::Round(int numRound, int reward)
	: currentWave(nullptr), numRound(numRound), reward(reward)
{
}

Round::Round(const Round& orig) = default;

Round& Round::operator=(const Round& round)
{
	if (this != &round)
	{
		this->numRound = round.numRound;
		this->reward = round.reward;
		this->ended = round.ended;
		this->waves = round.waves;
		this->currentWave = round.currentWave;
	}
	return *this;
}


void Round::startRound(Path& path)
{
	for (int i = 0; i < numWaves; ++i)
	{
		TypeEnemy type = TypeEnemy::sneaky;
		int numEnemies = 5;
		float delay = 5;
		float frecuency = 1;
		waves.emplace_back(path, i + 1, type, numEnemies, delay, frecuency);
	}
	
	currentWave = &waves.front();
	
	std::cout << toString() << std::endl;
	currentWave->startWave();
}

void Round::endRound()
{
	ended = true;
}

void Round::nextWave()
{
	waves.pop_front();

	if (!waves.empty())
	{
		currentWave = &waves.front();
		currentWave->startWave();
	}
	else
		endRound();
}


void Round::sendEnemy(float deltaTime)
{
	if (currentWave->isEnded())
		nextWave();
	else
		currentWave->sendEnemy(deltaTime);
}

std::string Round::toString() const
{
	std::stringstream ss;
	ss << "  Round " << numRound << " => " << reward << "$ ";
	return ss.str();
}
