#include "pch.h"
#include "Song.h"

#include "AudioManager.h"

Song::Song(std::string name)
	: name(name)
{
	song = Mix_LoadMUS(getPath().c_str());
	
	if (song == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Song Loading Failed %s", Mix_GetError());
	else
		std::cout << "Loaded Song: " << name << std::endl;
}

Song::~Song() = default;


std::string Song::getPath() const
{
	return musicFolderPath + name + ".mp3";
}

void Song::play(int repeat) const
{
	// Play (Channel, sound, loop x times)
	// 
	// Channel -1 = DEFAULT
	Mix_PlayMusic(song, repeat);
	//Mix_PlayMusic(music, repeat);
}

void Song::pause()
{
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void Song::resume()
{
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}
