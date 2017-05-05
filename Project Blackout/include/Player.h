#pragma once
#include "AnimSprite.h"
#include "InputManager.h"

class Player : public AnimSprite
{
public:
	Player(SDL_Renderer* rendererInput, char* fileName, int x, int y, int w, int h, int xFrames, int yFrames, InputManager* _input);
	~Player();

	void Update();
	void Draw();
private:
	InputManager* input = NULL;
	int checkXMove;
	int checkYMove;
};