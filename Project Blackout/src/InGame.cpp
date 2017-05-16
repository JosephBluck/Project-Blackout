#include "InGame.h"

InGame::InGame(SDL_Renderer* _renderer, InputManager* _input, GameStateManager* manager) :
	GameState(manager, _renderer)
{
	input = _input;
	bool initSuccess = false;
	
	collisionMap = new Sprite(renderer, "resources\\maps\\TestLevel\\ScreenOverlayScroll.png", 0, 0, 2560, 720);

	stateName = "In Game";

	if (!InitInGame())
	{
		exit = true;
	}

	int BREAKHERE = 0;
}

InGame::~InGame()
{
	if (initSuccess)
	{
		delete player;
	}

	SDL_DestroyTexture(cameraRenderBuffer);
	delete collisionMap;
}

bool InGame::InitInGame()
{
	player = new Player(renderer, "resources\\sprites\\Characters\\Player\\Player.png", 582, 100, 76, 157, 1, 1, input);
	if (!player)
	{
		return false;
	}
	cameraRenderBuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 2560, 720);
	//GIVE PLAYER COLLISION DATA
	LoadCollisionImage("resources\\maps\\TestLevel\\MapScrollTest.png", 2560, 720);
	player->UpdateCollisionMap(collisionPixels, 2560, 720);

	return true;
}

void InGame::Update()
{
	player->Update();
	UpdateCamera();

	if (input->WasKeyPressed(SDL_SCANCODE_P))
	{
		GS_Manager->AddState(new Paused(renderer,input ,GS_Manager));
	}
}

void InGame::UpdateCamera()
{
	camera.x = player->GetX() - 582;
	if (camera.x > 1280)
	{
		camera.x = 1280;
	}
	if (camera.x < 0)
	{
		camera.x = 0;
	}
}

void InGame::Draw()
{
	SDL_SetRenderTarget(renderer, cameraRenderBuffer);
	SDL_RenderClear(renderer);
	collisionMap->Draw();
	player->Draw();
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, cameraRenderBuffer, &camera, &screen);
}


void InGame::LoadCollisionImage(char* _filePath, int _w, int _h)
{
	//PNG MODE GOOOOOO
	unsigned int error;
	unsigned char* imageData = nullptr;
	unsigned int w = _w;
	unsigned int h = _h;

	error = lodepng_decode32_file(&imageData, &w, &h, _filePath);

	// store each pixel as an SDL_Color in a std::vec
	for (int i = 0; i < w * h; i++)
	{
		PixelData col;

		col.r = (int)imageData[(i * 4)];
		col.g = (int)imageData[(i * 4 + 1)];
		col.b = (int)imageData[(i * 4 + 2)];
		//col.a = (int)imageData[(i * 4 + 3)]; //DISREGARDING ALPHA CHANNEL

		collisionPixels.push_back(col);
	}
}

void InGame::DrawCollisionMap()
{
	collisionMap->Draw(0, 0);
}