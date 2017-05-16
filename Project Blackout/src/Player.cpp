#include "Player.h"

Player::Player(SDL_Renderer* rendererInput, char* fileName, int x, int y, int w, int h, int xFrames, int yFrames, InputManager* _input) :
	AnimSprite(rendererInput, fileName, x, y, w, h,xFrames,yFrames)
{
	input = _input;
	xMove = x;
	checkYMove = y;
	xSpeed = 10;

	jumpstate = Falling;
	hitFloor = false;
	hitRoof = false;
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
		isFlip = SDL_FLIP_NONE;
		isMovingX = true;
		checkXmove = xMove + xSpeed;
	}
	else if (aKeyPressed)
	{
		isFlip = SDL_FLIP_HORIZONTAL;
		isMovingX = true;
		isMovingLeft = true;
		checkXmove = xMove - xSpeed;
	}
	if (isMovingX && checkXmove <= 2445 && checkXmove >= 0)
	{
		xCollision = CheckXCollision();
	}
	posRect.x = xMove;
}

void Player::UpdateYMovement()
{
	bool wasWPressed = input->WasKeyPressed(SDL_SCANCODE_W);
	bool wasWReleased = input->WasKeyReleased(SDL_SCANCODE_W);
	
	//CHECK IF ABOVE AIR
	if (jumpstate == Standing) {
		if (CheckGravity())
		{
			jumpstate = Falling;
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
		ySpeed -= 7;
		break;
	}
	case Peak:
	{
		ySpeed *= 0.8 ;
		break;
	}
	case Falling:
	{
		if (ySpeed != maxFallSpeed)
		{
			ySpeed += 3;
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

	CheckYCollision();
	std::cout << jumpstate << "\n";
	posRect.y = checkYMove;
}

void Player::Draw()
{
	AnimSprite::Draw();
}

void Player::UpdateCollisionMap(std::vector<PixelData>& _collisionMap, int colWidth, int colHeight)
{
	collisionPixels = _collisionMap;
	collisionSize.w = colWidth;
	collisionSize.h = colHeight;

	int BREAK = 0;
}

bool Player::CheckXCollision()
{
	int xOffset;
	int yOffset = GetY();
	for (int i = 0; i < 10; i++)
	{
		if (isMovingLeft) {
			xOffset = GetX() - (xSpeed - i);
		}
		else {
			xOffset = GetX() + (xSpeed - i);
		}

		PixelData col;
		int checkPixel;
		if (!CheckPixelData(yOffset, xOffset, 'x'))
		{
			xMove = xOffset;
			return false;
		}
	}
	return true;
}

bool Player::CheckGravity()
{
	int xOffset = GetX();
	int yOffset = GetY() + 1;

	PixelData col;
	int checkPixel;

	if (CheckPixelData(yOffset, xOffset, 'x'))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Player::CheckYCollision()
{
	int xOffset = GetX();
	int yOffset = GetY() + ySpeed;

	PixelData col;
	int checkPixel;
	for (int i = 0; i < 50; i++)
	{
		if (CheckPixelData(yOffset, xOffset, 'y'))
		{
			if (hitRoof)
			{
				yOffset = GetY() + (ySpeed + i);
			}
			else if(hitFloor)
			{

				yOffset = GetY() + (ySpeed - i);
			}
		}
		else
		{
			if (hitFloor)
			{
				jumpstate = Over;
			}
			if (hitRoof)
			{
				jumpstate = Falling;
				ySpeed = 0;
			}
			hitFloor = false;
			hitRoof = false;
			checkYMove = yOffset;
			return false;
		}
	}

}

bool Player::CheckPixelData(int _offset, int _offset2, char axisBeingChecked)
{
	for (int checkY = _offset; checkY < _offset + GetHeight(); checkY++)
	{
		for (int checkX = _offset2; checkX < _offset2 + GetWidth(); checkX++)
		{
			checkPixel = (checkY * collisionSize.w) + checkX;
			col = collisionPixels[checkPixel];

			if (col.r == 0) {
				if (axisBeingChecked == 'y')
				{
					if (checkY <= _offset + (GetHeight() / 2))
					{
						hitRoof = true;
						hitFloor = false;
					}
					else
					{
						hitFloor = true;
						hitRoof = false;
					}
				}
				return true;
			}
		}
	}
	return false;
}