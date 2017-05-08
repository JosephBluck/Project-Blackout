#pragma once
#include "SDLInit.h"

class BitmapSprite
{
public:
	BitmapSprite(SDL_Renderer* rendererInput, char* fileName, int x, int y, int w, int h);
	~BitmapSprite();

	virtual void Draw();
	virtual void Draw(int x, int y);
	virtual void Draw(int x, int y, SDL_RendererFlip flip);

	void SetSize(int w, int h);

	bool isValid;

protected:
	SDL_Renderer* renderer;
	SDL_Rect posRect;
	SDL_Surface* loadImage;
	SDL_Texture* tex;
	SDL_RendererFlip isFlip;
};

