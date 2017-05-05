#pragma once
#include "GameStates.h"
#include"InputManager.h"
#include"SoundManager.h"
#include "Sprite.h"
#include "Player.h"

class InGame : public GameState
{
public:
	InGame(SDL_Renderer* _renderer, InputManager* _input, GameStateManager* manager);
	~InGame();

	void Update() override;
	void Draw() override;
private:
	bool InitInGame();
	bool initSuccess;

	Player* player;

	InputManager* input = NULL;//input manager
};