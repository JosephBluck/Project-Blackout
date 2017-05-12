#include "Paused.h"

Paused::Paused(SDL_Renderer* _renderer, InputManager* _input, GameStateManager* manager) :
	GameState(manager, _renderer)
{
	input = _input;
	initSuccess = false;

	stateName = "Paused";

	if (!InitPaused())
	{
		exit = true;
	}
}

Paused::~Paused()
{

}

bool Paused::InitPaused()
{
	pausedScreen = new Sprite(renderer, "resources\\sprites\\Paused\\Paused.png", 0, 0, 1280, 720);
	if (!pausedScreen)
	{
		return false;
	}
	return true;
}

void Paused::Update()
{
	if (input->WasKeyPressed(SDL_SCANCODE_P) && !input->IsKeyDown(SDL_SCANCODE_P))
	{
		delete pausedScreen;
		GS_Manager->RemoveLastState();
	}
}

void Paused::Draw()
{
	pausedScreen->Draw();
}