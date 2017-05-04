#include "AnimSprite.h"

AnimSprite::AnimSprite(SDL_Renderer* rendererInput, char* fileName, int x, int y, int totalWidth, int totalHeight, int xFrames, int yFrames) :
	Sprite (rendererInput, fileName, x, y, totalWidth, totalHeight)
{
	frameWidth = totalWidth / xFrames;
	frameHeight = totalHeight / yFrames;
	xFrame = 0;
	yFrame = 0;

	blit.x = 0;
	blit.y = 0;
	blit.w = frameWidth;
	blit.h = frameHeight;

	//Pos Rect overrides
	posRect.w = blit.w;
	posRect.h = blit.h;
}

AnimSprite::~AnimSprite()
{
	
}

void AnimSprite::Draw()
{
	if (isValid)
		SDL_RenderCopyEx(renderer, tex, &blit, &posRect, NULL, NULL, isFlip);
}

//Set the sprites position and draw
void AnimSprite::Draw(int x, int y)
{
	if (isValid) {
		posRect.x = x;
		posRect.y = y;
		SDL_RenderCopyEx(renderer, tex, &blit, &posRect, NULL, NULL, isFlip);
	}
}

//Position and Flip draw
void AnimSprite::Draw(int x, int y, SDL_RendererFlip flip)
{
	if (isValid) {
		posRect.x = x;
		posRect.y = y;
		isFlip = flip;

		SDL_RenderCopyEx(renderer, tex, &blit, &posRect, NULL, NULL, isFlip);
	}
}

void AnimSprite::SetFrame(int _xFrame, int _yFrame)
{
	blit.x = frameWidth * _xFrame;
	blit.y = frameHeight * _yFrame;
}