#pragma once
#include "pch.h"
#include "Sound.h"
#include "Song.h"

#define soundFolderPath AudioManager::getSoundFolderPath()
#define musicFolderPath AudioManager::getMusicFolderPath()

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	Sound* addSound(std::string soundName);
	Song* addSong(std::string songName);

	void playSound(std::string name);
	void playSong(std::string name);
	void playSong();
	void nextSong();

	static void playSoundInsta(std::string name);
	
	static void pauseMusic();
	static void resumeMusic();

	static void setSFXVolume(int volume) { Mix_Volume(-1, volume); }
	static void setMusicVolume(int volume) { Mix_VolumeMusic(volume); }
	void setSoundVolume(std::string soundName, int volume) { soundList.at(soundName).setVolume(volume); }

	void updateVolume() const;

	int& getVolume() { return globalVolume; }
	int& getSFXVolume() { return sfxVolume; }
	int& getMusicVolume() { return musicVolume; }
	
	static std::string getSoundFolderPath() { return "res/sounds/"; }
	static std::string getMusicFolderPath() { return "res/music/"; }

private:
	
	std::unordered_map<std::string, Sound> soundList;
	std::unordered_map<std::string, Song> musicList;
	
	// Song playing
	Song* currentSong;

	int audioRate = 44100;
	uint16_t audioFormat = MIX_DEFAULT_FORMAT;
	int audioChannels = 2;
	int audioBuffers = 4096;

	int globalVolume = 50;
	int sfxVolume = 50;
	int musicVolume = 50;
};

