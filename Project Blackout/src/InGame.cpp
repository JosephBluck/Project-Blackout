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
		delete player;
	}
}

bool InGame::InitInGame()
{
	player = new Player(renderer, "resources\\sprites\\Characters\\Player\\Player_Filler.png", 400, 100, 116, 171, 1, 1, input);
	if (!player)
	{
		return false;
	}
	return true;
}

void InGame::Update()
{
	player->Update();
}

void InGame::Draw()
{
	player->Draw();
}