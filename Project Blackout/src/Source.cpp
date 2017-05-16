#include "SDLInit.h"
#include "MainMenu.h"
#include "InputManager.h"

int main(int arc, char* args[])
{
	srand(time(NULL)); //Random Seeding

	//INITIALSE SDL AND THE WINDOW
	if (!InitSDL()) return -1;
	if (!InitExtensions()) return -2;

	SDL_Window* window;
	SDL_Renderer* renderer;

	if (!InitRenderer(window, renderer)) return -3;

	//INPUT MANAGER
	InputManager* input = new InputManager();

	//MAINMENU
	GameStateManager* manager = new GameStateManager();
	manager->AddState(new MainMenu(renderer, input, manager));

	
	while (!input->WasKeyPressed(SDL_SCANCODE_ESCAPE) && !manager->CheckStateExit()) {
		SDL_PumpEvents(); //KEEP EVENTS UP TO DATE
		//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer); //Clear Screen

		input->UpdateKeyboard();
		manager->UpdateState();
		manager->DrawState();

		SDL_RenderPresent(renderer); //Present Frame
	}

	delete input; //Delete the input manager
	delete manager;
	//DELETE WINDOW AND CLOSE SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();

	system("pause"); //Memory leak check
	return 0;
}