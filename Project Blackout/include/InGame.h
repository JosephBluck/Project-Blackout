#pragma once
#include "GameStates.h"
#include"InputManager.h"
#include"SoundManager.h"
#include "Sprite.h"
#include "Player.h"
#include "BitmapSprite.h"

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

	void LoadCollisionImage(char* _filePath);

	Sprite* image;		  // sprite that this bkg uses
	Sprite* collisionMap; // collision image that this bkg uses

	std::vector<SDL_Color> collisionPixels; // store the collision pixel data in here
	SDL_Rect collisionSize;					// size of collision map
	bool showCollisionMap;					// for debug purposes (press C & V to show / hide)

	float   x;      // current x position (changes as scrolls)
	float   y;      // current y position (changes as scrolls)
	int     w;		// width of image used
	int     h;      // height of image used

	void DrawCollisionMap();
};