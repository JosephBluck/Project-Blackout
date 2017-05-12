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

	void UpdateCollisionMap(std::vector<PixelData>& _collisionMap, int colWidth, int colHeight);

private:
	std::vector<PixelData> collisionPixels; // store the collision pixel data in here
	SDL_Rect collisionSize;

	InputManager* input = NULL;
	int xMove;
	int checkXmove;
	int checkYMove;

	int collisionCorrection = 0; //Controls the direction of positional correction on the x-axis
	int yFallDifference; //Calculation variable for snapping player to floor when falling or walking into walls
	int xFallDifference;
	bool isMovingLeft;

	int ySpeed;
	int xSpeed;

	void UpdateXMovement();
	void UpdateYMovement();

	bool CheckXCollision();
	bool CheckYCollision();
	bool CheckPixelData(int _offset, int _offset2, char axisBeingChecked);
	PixelData col;
	int checkPixel;

	enum JumpState
	{
		Standing, Raising, Peak, Falling, Over
	};
	JumpState jumpstate; 

	int yMaxHeight;
	int maxFallSpeed = 30;
};