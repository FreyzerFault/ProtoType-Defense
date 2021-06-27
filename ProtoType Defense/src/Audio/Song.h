#pragma once
#include "pch.h"

class Song
{
public:
	Song(std::string name);
	~Song();
	
	std::string getPath() const;
	std::string getName() const { return name; }
	
	void play(int repeat = 0) const;

	static void pause();
	static void resume();

private:
	std::string name;
	Mix_Music* song;
};

