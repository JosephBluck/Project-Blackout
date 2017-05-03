#include "SDLInit.h"
#include "MainMenu.h"

int main(int arc, char* args[])
{
	srand(time(NULL)); //Random Seeding

	//INITIALSE SDL AND THE WINDOW
	if (!InitSDL()) return -1;
	if (!InitExtensions()) return -2;

	SDL_Window* window;
	SDL_Renderer* renderer;

	if (!InitRenderer(window, renderer)) return -3;

	//MAINMENU
	MainMenu* menu = NULL;
	menu = new MainMenu(renderer);

	if (menu->InitMenu()) {
		//MENU LOOP
		while (!CheckExit()) {
			SDL_RenderClear(renderer);

			menu->Update();

			SDL_RenderPresent(renderer);
		}
	}

	//DELETE WINDOW AND CLOSE SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();

	return 0;
}