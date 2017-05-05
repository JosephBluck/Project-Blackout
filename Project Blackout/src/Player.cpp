#include "Player.h"

Player::Player(SDL_Renderer* rendererInput, char* fileName, int x, int y, int w, int h, int xFrames, int yFrames, InputManager* _input) :
	AnimSprite(rendererInput, fileName, x, y, w, h,xFrames,yFrames)
{
	input = _input;
	checkXMove = 0;
	checkYMove = 0;
}

Player::~Player()
{

}

void Player::Update()
{

}

void Player::Draw()
{
	AnimSprite::Draw();
}