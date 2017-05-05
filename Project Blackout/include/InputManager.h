#pragma once
#include "SDLInit.h"
#include <map>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void UpdateKeyboard();

	bool WasKeyPressed(SDL_Scancode _key);
	bool IsKeyDown(SDL_Scancode _key);
	bool WasKeyReleaced(SDL_Scancode _key);
private:
	int numKeys;
	Uint8* currentKeys;
	Uint8* prevFrameKeys;
};