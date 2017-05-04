#pragma once
#include "Sprite.h"

class AnimSprite : public Sprite
{
public:
	AnimSprite(SDL_Renderer* rendererInput, char* fileName, int x, int y, int totalWidth, int totalHeight, int xFrames, int yFrames);
	~AnimSprite();

	//Animsprite function overrides
	void Draw() override;
	void Draw(int x, int y) override;
	void Draw(int x, int y, SDL_RendererFlip flip) override;

	void SetFrame(int _xFrame, int _yFrame);

private:
	SDL_Rect blit;
	int frameWidth;
	int frameHeight;

	int xFrame;
	int yFrame;
};