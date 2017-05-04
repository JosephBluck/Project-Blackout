#include "SoundManager.h"

//Non-BGM
SoundManager::SoundManager(int _soundCount) 
{
	hasBGM = false;
	soundCount = _soundCount;

	if (soundCount > 0) {
		sounds = new Mix_Chunk[soundCount]{ NULL };
	}
}

//BGM
SoundManager::SoundManager(int _soundCount, char* musicFile)
{
	soundCount = _soundCount;

	if (soundCount > 0) {
		sounds = new Mix_Chunk[soundCount];
	}

	bgm = Mix_LoadMUS(musicFile);

	if (bgm != NULL) {
		//std::cout << "BGM SUCCESSFULLY LOADED FROM " << musicFile << "\n"; //Debugging Lines
		hasBGM = true; //BGM Successfully loaded
	}
	else {
		//std::cout << "BGM Loading unsuccessful! " << Mix_GetError() << "\n"; //Debugging Lines
	}
}

SoundManager::~SoundManager()
{
	if (hasBGM) {
		Mix_FreeMusic(bgm);
		delete bgm;
	}

	for (int i = 0; i < soundCount; i++) {
		Mix_FreeChunk(&sounds[i]);
		delete &sounds[i];
	}
}

//LOADING Sound into manager
bool SoundManager::LoadSound(int soundID, char* filepath)
{
	if (soundID >= 0 && soundID < soundCount) { //Prevent array overloading
		sounds[soundID] = *Mix_LoadWAV(filepath);

		if (&sounds[soundID] != NULL) { //Check if load is successful
			return true; //Load was successful
		}
		else {
			return false; //File was either inaccessible or filepath was wrong
		}
	}

	return false; //SoundID is either negative or too high, return failure on loading
}

//Playing Sound from manager
bool SoundManager::PlaySound(int soundID)
{
	if (soundID >= 0 && soundID < soundCount) { //Prevent array overloading
		if (&sounds[soundID] != NULL) { //Check the sound is valid
			Mix_PlayChannel(-1, &sounds[soundID], 0); //Play Sound
		}

	}

	return false; //Failure either due to invalid soundID or unloaded sound
}

bool SoundManager::PlayBGM(int loops)
{
	if (hasBGM) {
		Mix_PlayMusic(bgm, loops);
		return true;
	}

	return false;
}