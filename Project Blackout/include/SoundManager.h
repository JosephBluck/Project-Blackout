#pragma once
#include "SDLInit.h"

class SoundManager {
public:
	SoundManager(int _soundCount); //Initialise sound-only soundmanager
	SoundManager(int _soundCount, char* musicFile); //Initialise soundmanager with a BGM track
	~SoundManager();

	bool LoadSound(int soundID, char* filepath); //Load Soundfile into manager

	bool PlaySound(int soundID);
	bool PlayBGM(int loops);

private:
	bool hasBGM;
	int soundCount;

	Mix_Chunk* sounds;
	Mix_Music* bgm;
};