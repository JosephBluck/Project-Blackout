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
	MainMenu* menu = NULL;
	menu = new MainMenu(renderer, input);

	if (menu->InitMenu()) {
		//MENU LOOP
		while (!input->keys[SDL_SCANCODE_ESCAPE] && !menu->exit) {
			SDL_PumpEvents(); //KEEP EVENTS UP TO DATE
			SDL_RenderClear(renderer); //Clear Screen

			menu->Update();

			SDL_RenderPresent(renderer); //Present Frame
		}
	}

	delete input; //Delete the input manager

	//DELETE WINDOW AND CLOSE SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();

	system("pause"); //Memory leak check
	return 0;
}