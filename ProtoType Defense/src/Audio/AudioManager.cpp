#include "pch.h"
#include "AudioManager.h"


AudioManager::AudioManager()
	: currentSong(nullptr)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL AUDIO Loading ERROR!!" << std::endl;
		return;
	}

	if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
		exit(-1);
	}
}

AudioManager::~AudioManager()
{
	Mix_CloseAudio();
	Mix_Quit();
}

Sound* AudioManager::addSound(std::string soundName)
{
	return &soundList.try_emplace(soundName, soundName).first->second;
}

Song* AudioManager::addSong(std::string songName)
{
	auto it = musicList.try_emplace(songName, songName).first;
	return currentSong = &it->second;
}

void AudioManager::playSound(std::string name)
{
	addSound(name)->play();
}

void AudioManager::playSong(std::string name)
{
	currentSong = addSong(name);
	currentSong->play();
	std::cout << "Playing " + name << std::endl;
}

void AudioManager::playSong()
{
	if (currentSong != nullptr)
		playSong(currentSong->getName());
}

void AudioManager::nextSong()
{
	auto it = ++musicList.find(currentSong->getName());
	if (it == musicList.end()) it = musicList.begin();
	playSong(it->first);
}

void AudioManager::playSoundInsta(std::string name)
{
	Mix_Chunk* sound = Mix_LoadWAV((soundFolderPath + name + ".wav").c_str());

	if (sound == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Sound Loading Failed %s", Mix_GetError());

	Mix_PlayChannel(-1, sound, 0);
}

void AudioManager::pauseMusic()
{
	Song::pause();
}

void AudioManager::resumeMusic()
{
	Song::resume();
}

void AudioManager::updateVolume() const
{
	Mix_Volume(-1, sfxVolume * globalVolume / 100);
	Mix_VolumeMusic(musicVolume * globalVolume / 100);
}
