#pragma once
#include "SDLInit.h"
#include "GameStates.h"
#include "GSManager.h"
#include"InputManager.h"
#include"SoundManager.h"
#include "Sprite.h"
#include "Player.h"
#include "BitmapSprite.h"
#include "Paused.h"

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

	void UpdateCamera();
	SDL_Rect camera{ 0,0,1280,720 };
	SDL_Rect screen{ 0,0,1280,720 };
	SDL_Texture* cameraRenderBuffer;

	Player* player;

	InputManager* input = NULL;//input manager

	void LoadCollisionImage(char* _filePath, int _w, int _h);

	Sprite* image;		  // sprite that this bkg uses
	Sprite* collisionMap; // collision image that this bkg uses

	std::vector<PixelData> collisionPixels; // store the collision pixel data in here
	SDL_Rect collisionSize;					// size of collision map
	bool showCollisionMap;					// for debug purposes (press C & V to show / hide)

	float   x;      // current x position (changes as scrolls)
	float   y;      // current y position (changes as scrolls)
	int     w;		// width of image used
	int     h;      // height of image used

	void DrawCollisionMap();
};
