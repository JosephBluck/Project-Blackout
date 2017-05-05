#include "TextSprite.h"

TextSprite::TextSprite(SDL_Renderer* rendererInput, AnimSprite* textSprite, int x, int y)
{
	textData = textSprite;
	xPos = x;
	yPos = y;
}

TextSprite::~TextSprite()
{

}

void TextSprite::Draw()
{
	//Update character height and width incase the sprite has been resized
	charWidth = textData->GetWidth();
	charHeight = textData->GetHeight();

	//DRAW OUT WHOLE MESSAGE IN ONE
	//Chars are converted to ints according to ASCII, see here for more info: http://www.asciitable.com/

	for (int i = 0; i < messageLength; i++) {
		if (message[i] > 64 && message[i] < 91) { //CAPITAL LETTERS
			textData->SetFrame(message[i] - 65, 0);
		}
		else if (message[i] > 96 && message[i] < 123) { //LOWER CASE LETTERS
			textData->SetFrame(message[i] - 97, 1);
		}
		else if (message[i] > 43 && message[i] < 59) { //PUNCTUATION AND NUMBERS
			textData->SetFrame(message[i] - 44, 2);
		}
		else { textData->SetFrame(0, 3); } //SPACES

		textData->Draw(xPos + (i * charWidth), yPos);
	}
}

void TextSprite::SetText(char* text)
{
	message = text;
	messageLength = strlen(message); //Gets the message length
}