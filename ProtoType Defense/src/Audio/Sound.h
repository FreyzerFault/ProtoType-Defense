#pragma once
#include "pch.h"

class Sound
{
public:
	Sound(std::string name);
	~Sound();

	std::string getPath() const;
	std::string getName() const { return name; }

	void play(int repeat = 0, int channel = -1) const;

	void setVolume(int volume) const;

	Mix_Chunk* getChunk() const { return sound; }

private:
	std::string name;
	Mix_Chunk* sound;
};
