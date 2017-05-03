#include "Sprite.h"

//Set up intial position and dimensions and load an image into the class
Sprite::Sprite(SDL_Renderer* rendererInput, char* fileName, int x, int y, int w, int h) 
{
	isValid = false;
	tex = NULL;

	renderer = rendererInput;
	tex = IMG_LoadTexture(renderer, fileName);

	posRect.x = x;
	posRect.y = y;
	posRect.w = w;
	posRect.h = h;

	//CHECK IF FILE HAS LOADED CORRECTLY
	if (tex != NULL)
		isValid = true;
}

//Free up memory
Sprite::~Sprite()
{
	SDL_DestroyTexture(tex);
}

//Draw at its current position
void Sprite::Draw()
{
	if (isValid)
		SDL_RenderCopyEx(renderer, tex, NULL, &posRect, NULL, NULL, isFlip);
}

//Set the sprites position and draw
void Sprite::Draw(int x, int y)
{
	if (isValid) {
		posRect.x = x;
		posRect.y = y;
		SDL_RenderCopyEx(renderer, tex, NULL, &posRect, NULL, NULL, isFlip);
	}
}

//Position and Flip draw
void Sprite::Draw(int x, int y, SDL_RendererFlip flip)
{
	if (isValid) {
		posRect.x = x;
		posRect.y = y;
		isFlip = flip;

		SDL_RenderCopyEx(renderer, tex, NULL, &posRect, NULL, NULL, isFlip);
	}
}

void Sprite::SetSize(int w, int h)
{
	posRect.w = w;
	posRect.h = h;
}