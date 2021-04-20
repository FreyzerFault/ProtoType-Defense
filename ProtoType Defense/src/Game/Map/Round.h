#pragma once
#include <list>

#include "Wave.h"
class Path;

class Round
{
public:
	Round(Path& path);

	void startRound();
	void sendWave();
	void sendEnemy() const;
	
	static int getReward();

	Wave& getWave() const { return *currentWave; }

private:
	std::list<Wave> waves;
	Wave* currentWave;
};

