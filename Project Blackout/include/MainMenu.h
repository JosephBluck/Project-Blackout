#pragma once
#include "SDLInit.h"
#include "Sprite.h"
#include "MathFunctions.h"
#include "FloatingParticle.h"

class MainMenu
{
public:
	MainMenu(SDL_Renderer* rendererInput);
	~MainMenu();
	bool InitMenu();

	void Update();

private:
	SDL_Renderer* renderer;
	bool initSuccess;

	Sprite* title1 = NULL;
	Sprite* title2 = NULL;
	Sprite* flash = NULL;
	Sprite* particle = NULL;
	Sprite* backGlow = NULL;

	//TIMER
	int timer;

	//Animation Functions
	void Intro();

	std::vector<FloatParticle*>menuParticles;
};