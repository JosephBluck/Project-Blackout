#include "InGame.h"

InGame::InGame(SDL_Renderer* _renderer, InputManager* _input, GameStateManager* manager) :
	GameState(manager, _renderer)
{
	input = _input;
	bool initSuccess = false;
	
	collisionMap = new Sprite(renderer, "resources\\maps\\TestLevel\\screen1.png", 0, 0, 1280, 720);

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

	delete collisionMap;
}

bool InGame::InitInGame()
{
	player = new Player(renderer, "resources\\sprites\\Characters\\Player\\Player_Filler.png", 400, 100, 116, 171, 1, 1, input);
	if (!player)
	{
		return false;
	}

	//GIVE PLAYER COLLISION DATA
	LoadCollisionImage("resources\\maps\\TestLevel\\Screen1.bmp");
	player->UpdateCollisionMap(collisionPixels, 1280, 720);

	return true;
}

void InGame::Update()
{
	collisionMap->Draw(0, 0);
	player->Update();
}

void InGame::Draw()
{
	player->Draw();
	collisionMap->Draw();
}


void InGame::LoadCollisionImage(char* _filePath)
{
	SDL_PixelFormat *fmt;
	SDL_Surface *collisionSurface;
	Uint32 temp;
	Uint32* pixels;

	collisionSurface = SDL_LoadBMP(_filePath);
	collisionSize.w = collisionSurface->w;
	collisionSize.h = collisionSurface->h;

	fmt = collisionSurface->format;
	SDL_LockSurface(collisionSurface);
	pixels = (Uint32*)collisionSurface->pixels;
	SDL_UnlockSurface(collisionSurface);

	// store each pixel as an SDL_Color in a std::vec
	for (int i = 0; i < collisionSurface->w * collisionSurface->h; i++)
	{
		SDL_Color col;

		/* Get Red component */
		temp = pixels[i] & fmt->Rmask;  /* Isolate red component */
		temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
		col.r = (Uint8)temp;

		/* Get Green component */
		temp = pixels[i] & fmt->Gmask;  /* Isolate green component */
		temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
		col.g = (Uint8)temp;

		/* Get Blue component */
		temp = pixels[i] & fmt->Bmask;  /* Isolate blue component */
		temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
		col.b = (Uint8)temp;

		/* Get Alpha component */
		temp = pixels[i] & fmt->Amask;  /* Isolate alpha component */
		temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
		temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
		col.a = (Uint8)temp;

		collisionPixels.push_back(col);
	}

	SDL_FreeSurface(collisionSurface);
}

void InGame::DrawCollisionMap()
{
	collisionMap->Draw(0, 0);
}