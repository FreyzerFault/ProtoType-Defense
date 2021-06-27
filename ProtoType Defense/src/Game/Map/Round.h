#pragma once
#include "pch.h"

#include "Wave.h"

class Path;

static int baseReward = 100;

class Round
{
public:
	Round();
	Round(int numRound, int reward = baseReward);
	Round(const Round& orig);

	Round& operator=(const Round& round);

	void startRound(Path& path);
	void endRound();
	void nextWave();

	Wave& getWave() const { return *currentWave; }
	int getReward() const { return reward; }

	bool isEnded() const { return ended; }

	void sendEnemy(float deltaTime);

	std::string toString() const;

private:
	std::list<Wave> waves;
	Wave* currentWave;

	int numRound;
	int reward; // Money income when round is completed

	bool ended = false;
	
};


