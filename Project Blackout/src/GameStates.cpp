#include "GameStates.h"

GameState::GameState(GameStateManager* _gsManager, SDL_Renderer* _renderer)
{
	this->GS_Manager = _gsManager;
	this->renderer = _renderer;
	exit = false;
}

GameState::~GameState()
{
	std::cout << "THE BASE GAMESTATE CLASS HAS KAPUT!\n";
}

void GameState::Update()
{
	//will be filled in the real states
}

void GameState::Draw()
{
	//will be filled in the real states
}