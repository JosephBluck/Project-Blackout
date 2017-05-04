#include "InputManager.h"

InputManager::InputManager()
{
	keys = SDL_GetKeyboardState(NULL);
}

InputManager::~InputManager()
{

}
