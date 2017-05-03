#pragma once
#include "SDLInit.h"

class Sprite
{
public:
	Sprite(SDL_Renderer* rendererInput, char* fileName, int x, int y, int w, int h);
	~Sprite();

	virtual void Draw();
	virtual void Draw(int x, int y);
	virtual void Draw(int x, int y, SDL_RendererFlip flip);

	void SetSize(int w, int h);

	bool isValid;

protected:
	SDL_Renderer* renderer;
	SDL_Rect posRect;
	SDL_Texture* tex;
	SDL_RendererFlip isFlip;
};