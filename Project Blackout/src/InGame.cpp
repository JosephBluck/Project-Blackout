#include "InGame.h"

InGame::InGame(SDL_Renderer* _renderer, InputManager* _input, GameStateManager* manager) :
	GameState(manager, _renderer)
{
	input = _input;
	bool initSuccess = false;

	stateName = "In Game";

	if (!InitInGame())
	{
		exit = true;
	}
}

InGame::~InGame()
{
	if (initSuccess)
	{
	}
}

bool InGame::InitInGame()
{
	return true;
}

void InGame::Update()
{

}

void InGame::Draw()
{

}