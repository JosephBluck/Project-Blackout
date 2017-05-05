#include "GameStates.h"

GameState::GameState(GameStateManager* _gsManager, SDL_Renderer* _renderer)
{
	this->GS_Manager = _gsManager;
	this->renderer = _renderer;
}

void GameState::Update()
{
	//will be filled in the real states
}

void GameState::Draw()
{
	//will be filled in the real states
}