#pragma once
#include "AnimSprite.h"

class TextSprite
{
public:
	TextSprite(SDL_Renderer* rendererInput, AnimSprite* textSprite, int x, int y);
	~TextSprite();

	void Draw();
	void SetText(char* text);

private:
	AnimSprite* textData = NULL;
	char* message = NULL;
	int messageLength = 0;

	int xPos, yPos, charWidth, charHeight;
};