#include "Player.h"

Player::Player(SDL_Renderer* rendererInput, char* fileName, int x, int y, int w, int h, int xFrames, int yFrames, InputManager* _input) :
	AnimSprite(rendererInput, fileName, x, y, w, h,xFrames,yFrames)
{
	input = _input;
	xMove = x;
	checkXmove = x;
	checkYMove = y;
	xSpeed = 10;

	jumpstate = Falling;
}

Player::~Player()
{

}

void Player::Update()
{
	UpdateXMovement();
	UpdateYMovement();
}

void Player::UpdateXMovement()
{
	bool dKeyPressed = input->IsKeyDown(SDL_SCANCODE_D);
	bool aKeyPressed = input->IsKeyDown(SDL_SCANCODE_A);

	if (dKeyPressed)
	{
		checkXmove = xMove + xSpeed;
	}
	if (aKeyPressed)
	{
		checkXmove = xMove - xSpeed;
	}

	if (checkXmove <= 2444 && checkXmove >= 0)
	{
		xMove = checkXmove;
	}
	posRect.x = xMove;
}

void Player::UpdateYMovement()
{
	bool wasWPressed = input->WasKeyPressed(SDL_SCANCODE_SPACE);
	bool wasWReleaced = input->WasKeyReleased(SDL_SCANCODE_SPACE);
	

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
		if (wasWReleaced || (checkYMove <= yMaxHeight))
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
		if (checkYMove >= 500)
		{
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
	if (checkYMove > 500) {
		checkYMove = 500;
	}
	posRect.y = checkYMove;
}

void Player::Draw()
{
	AnimSprite::Draw();
}