#pragma once
#include "SDLInit.h"
#include "Sprite.h"
#include "AnimSprite.h"
#include "MathFunctions.h"
#include "FloatingParticle.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "GSManager.h"
#include "TextSprite.h"
#include "InGame.h"
#include "Intro.h"

class MainMenu : public GameState
{
public:
	MainMenu(SDL_Renderer* rendererInput, InputManager* _input, GameStateManager* manager);
	~MainMenu();
	bool InitMenu();

	void Update() override;

private:
	bool initSuccess;
	bool startGame = false;

	InputManager* input = NULL;//INPUT

	//Main details
	Sprite* title1 = NULL;
	Sprite* title2 = NULL;
	Sprite* flash = NULL;
	Sprite* particle = NULL;
	Sprite* backGlow = NULL;

	//BUTTONS
	Sprite* newGameButton = NULL;
	Sprite* loadGameButton = NULL;
	Sprite* optionsButton = NULL;
	Sprite* exitButton = NULL;

	Sprite* cursorSprite = NULL; //Cursor Sprite

	//Mouseinput
	void MouseInput();
	int mouseX = 0;
	int mouseY = 0;
	int hover = 0;
	int deltaHover = 0; //Checks if the current hoverstate of the mouse is different

	//SOUNDS
	SoundManager* menuSounds = NULL;

	//TIMER
	int timer;

	//Animation Functions
	void Intro();

	Uint32 mouseState; //Mouse button variable

	std::vector<FloatParticle*>menuParticles;
	
	//PRIVATE FUNCTIONS
	void MenuIdle();
	
	//TEXT TESTING
	AnimSprite* monoFont = NULL;
	TextSprite* textTest = NULL;

	bool jumpToGameLoop = false;
};