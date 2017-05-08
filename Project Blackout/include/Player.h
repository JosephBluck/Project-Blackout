#pragma once
#include "AnimSprite.h"
#include "InputManager.h"
#include <iostream>

class Player : public AnimSprite
{
public:
	Player(SDL_Renderer* rendererInput, char* fileName, int x, int y, int w, int h, int xFrames, int yFrames, InputManager* _input);
	~Player();

	void Update();
	void Draw();

	int GetXMove() { return xMove; }
private:
	InputManager* input = NULL;
	int xMove;
	int checkXmove;
	int checkYMove;

	int ySpeed;
	int xSpeed;

	void UpdateXMovement();
	void UpdateYMovement();

	enum JumpState
	{
		Standing, Raising, Peak, Falling, Over
	};
	JumpState jumpstate;

	int yMaxHeight;
	int maxFallSpeed = 30;
};