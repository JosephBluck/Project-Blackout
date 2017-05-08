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
		delete background;
	}
	SDL_DestroyTexture(cameraRenderBuffer);
}

bool InGame::InitInGame()
{
	player = new Player(renderer, "resources\\sprites\\Characters\\Player\\Player_Filler.png", 582, 100, 116, 171, 1, 1, input);
	background = new AnimSprite(renderer, "resources\\sprites\\Test camera map.png", 0, 0, 2560, 720, 1, 1);
	cameraRenderBuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 2560, 720);
	if (!player || !background)
	{
		return false;
	}
	return true;
}

void InGame::Update()
{
	player->Update();
	UpdateCamera();
}

void InGame::UpdateCamera()
{
	Camera.x = player->GetX() - 582;
	if (Camera.x > 1280)
	{
		Camera.x = 1280;
	}
	if (Camera.x < 0)
	{
		Camera.x = 0;
	}
}

void InGame::Draw()
{
	SDL_SetRenderTarget(renderer, cameraRenderBuffer);
	background->Draw();
	player->Draw();
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, cameraRenderBuffer, &Camera, &screen);
}