#include <SDL.h>
#include <SDL_image.h>
#include <string>

class GameStateManager;

class GameState
{
public:
	GameState(GameStateManager* _gsManager, SDL_Renderer* _renderer);//initialise GameStates

	virtual void Update();
	virtual void Draw();
protected:
	GameStateManager* GS_Manager;//GameStateManager used
	SDL_Renderer* renderer;//SDL Renderer used
	std::string stateName;//Game state name
	const Uint8* key = SDL_GetKeyboardState(NULL);//Keyboard Input
	int mouseX;//mouse position x
	int mouseY;//mouse position y
};
