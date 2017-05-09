#include "Player.h"

Player::Player(SDL_Renderer* rendererInput, char* fileName, int x, int y, int w, int h, int xFrames, int yFrames, InputManager* _input) :
	AnimSprite(rendererInput, fileName, x, y, w, h,xFrames,yFrames)
{
	input = _input;
	xMove = x;
	checkYMove = y;
	xSpeed = 10;

	jumpstate = Falling;
}

Player::~Player()
{

}

void Player::Update()
{
	UpdateYMovement();
	UpdateXMovement();
}

void Player::UpdateXMovement()
{
	bool canMove;

	bool dKeyPressed = input->IsKeyDown(SDL_SCANCODE_D);
	bool aKeyPressed = input->IsKeyDown(SDL_SCANCODE_A);

	bool xCollision = false;
	bool isMovingX = false;
	isMovingLeft = false;

	if (dKeyPressed)
	{
		isMovingX = true;
		checkXmove = xMove + xSpeed;
		collisionCorrection = 1;
		xCollision = CheckXCollision();
	}
	else if (aKeyPressed)
	{
		isMovingX = true;
		isMovingLeft = true;
		checkXmove = xMove - xSpeed;
		collisionCorrection = -1;
		xCollision = CheckXCollision();
	}

	if (checkXmove <= 2445 && checkXmove >= 0 && !xCollision)
	{
		xMove = checkXmove;
	}
	else {
		checkXmove = xMove;
		if (isMovingX) {
			if (isMovingLeft) {
				xMove -= fallDifference;
			}
			else {
				xMove += fallDifference;
			}
		}
	}

	posRect.x = xMove;
}

void Player::UpdateYMovement()
{
	bool wasWPressed = input->WasKeyPressed(SDL_SCANCODE_W);
	bool wasWReleased = input->WasKeyReleased(SDL_SCANCODE_W);
	
	//CHECK IF ABOVE AIR
	if (jumpstate == Standing) {
		ySpeed = 1;

		if (!CheckYCollision()) {
			jumpstate = Falling;
		}
		else{
			ySpeed = 0;
		}
	}

	switch(jumpstate)
	{
	case JumpState::Standing:
	{
		if(wasWPressed)
		{
			yMaxHeight = posRect.y - 100;
			jumpstate = Raising;
		}
		break;
	}
	case JumpState::Raising:
	{
		if (wasWReleased || (checkYMove <= yMaxHeight))
		{
			jumpstate = Peak;
		}
		break;
	}
	case JumpState::Peak:
	{
		if (ySpeed < 1)
		{
			jumpstate = Falling;
		}
		break;
	}
	case JumpState::Falling:
	{
		bool hitFloor = CheckYCollision();
		if (checkYMove >= 500 || hitFloor)
		{
			if (hitFloor) {
				checkYMove += fallDifference;
			}

			jumpstate = Over;
		}
		break;
	}
	}

	switch (jumpstate)
	{
	case Raising:
	{
		ySpeed -= 5;
		break;
	}
	case Peak:
	{
		ySpeed += 2;
		break;
	}
	case Falling:
	{
		if (ySpeed != maxFallSpeed)
		{
			ySpeed += 6;
		}
		break;
	}
	case Over:
	{
		ySpeed = 0;
		jumpstate = Standing;
		break;
	}
	}

	checkYMove += ySpeed;

	posRect.y = checkYMove;
}

void Player::Draw()
{
	AnimSprite::Draw();
}

void Player::UpdateCollisionMap(std::vector<SDL_Color>& _collisionMap, int colWidth, int colHeight)
{
	collisionPixels = _collisionMap;
	collisionSize.w = colWidth;
	collisionSize.h = colHeight;

	int BREAK = 0;
}

bool Player::CheckXCollision()
{
	int xOffset;

	if (isMovingLeft) {
		xOffset = GetX() - xSpeed;
	}
	else {
		xOffset = GetX() + xSpeed;
	}

	int yOffset = GetY();

	SDL_Color col;
	int checkPixel;

	for (int checkY = yOffset; checkY < yOffset + GetHeight(); checkY++)
	{
		for (int checkX = xOffset; checkX < xOffset + GetWidth(); checkX++)
		{
			checkPixel = (checkY * collisionSize.w) + checkX;
			col = collisionPixels[checkPixel];

			if (col.r == 0) {

				if (!isMovingLeft) {
					fallDifference = checkX - (GetX() + GetWidth());
				}
				else {
					fallDifference = checkX - (GetX() + GetWidth());

					while (fallDifference < -xSpeed) {
						fallDifference += xSpeed;
					}
				}

				std::cout << "CORRECTING BY: " << fallDifference << "\n";

				return true;
			}
		}
	}

	return false;
}

bool Player::CheckYCollision()
{
	int xOffset = GetX();
	int yOffset = GetY() + ySpeed;

	SDL_Color col;
	int checkPixel;

	for (int checkY = yOffset; checkY < yOffset + GetHeight(); checkY++)
	{
		for (int checkX = xOffset; checkX < xOffset + GetWidth(); checkX++)
		{
			checkPixel = (checkY * collisionSize.w) + checkX;
			col = collisionPixels[checkPixel];

			if (col.r == 0) {
				fallDifference = checkY - (GetY() + GetHeight());

				return true;
			}
		}
	}

	return false;
}

