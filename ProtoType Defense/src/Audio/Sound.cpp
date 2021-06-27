#include "pch.h"
#include "Sound.h"

#include "AudioManager.h"

Sound::Sound(std::string name)
	: name(name)
{
	sound = Mix_LoadWAV(getPath().c_str());
	
	if (sound == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Sound Loading Failed %s", Mix_GetError());
	else
		std::cout << "Loaded Sound: " << name << std::endl;
}

std::string Sound::getPath() const
{
	return soundFolderPath + name + ".wav";
}

Sound::~Sound() = default;

void Sound::play(int repeat, int channel) const
{
	// Play (Channel, sound, loop x times)
	// 
	// Channel -1 = DEFAULT
	Mix_PlayChannel(channel, sound, repeat);
}

void Sound::setVolume(int volume) const
{
	Mix_VolumeChunk(sound, volume);
}
