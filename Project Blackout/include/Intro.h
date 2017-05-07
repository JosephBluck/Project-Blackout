#pragma once
#include "GameStates.h"
#include "MainMenu.h"

class IntroState : public GameState
{
public:
	IntroState(SDL_Renderer* _renderer, GameStateManager* _gsManager, InputManager* _input);
	~IntroState();

	void Update() override;
	//void Draw() override;

private:
	InputManager* input = NULL;

	//Text setup
	AnimSprite* monoFont = NULL;
	TextSprite* introText = NULL;
	
	SoundManager* introSounds = NULL;
};