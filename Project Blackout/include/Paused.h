#pragma once
#include "GameStates.h"
#include "GSManager.h"
#include"InputManager.h"
#include"SoundManager.h"
#include "Sprite.h"

class Paused : public GameState
{
public:
	Paused(SDL_Renderer* _renderer, InputManager* _input, GameStateManager* manager);
	~Paused();

	void Update() override;
	void Draw() override;
private:
	bool InitPaused();
	bool initSuccess;

	InputManager* input = NULL;

	Sprite* pausedScreen;
};
