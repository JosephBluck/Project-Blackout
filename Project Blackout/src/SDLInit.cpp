#include "SDLInit.h"

const Uint8 *keyInput = SDL_GetKeyboardState(NULL);

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "ERROR! SDL has failed to initialise: " << SDL_GetError() << "\n";
		system("pause");
		return false;
	}

	return true;
}

bool InitExtensions()
{
	//Initialise PNG Loading Extension
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cout << "SDL PNG Failed to Initialise: " << IMG_GetError() << " \n";
		system("pause");
		return false;
	}

	//Initialise SDL Mixer for sound and music
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "SDL Mixer failed to initialise: " << Mix_GetError() << "\n";
		system("pause");
		return false;
	}

	return true;
}

bool InitRenderer(SDL_Window* &window, SDL_Renderer* &renderer)
{
	window = SDL_CreateWindow("Project: BlackOUT", 10, 50, 1280, 720, SDL_WINDOW_SHOWN); //INIT WINDOW

	if (window == NULL) {
		std::cout << "Could not create window: " << SDL_GetError() << "\n";
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //INIT RENDERER
	if (renderer == NULL) {
		std::cout << "Could not create renderer: " << SDL_GetError() << " \n";
		return false;
	}

	return true;
}

//Check Exit Function
bool CheckExit()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || keyInput[SDL_SCANCODE_ESCAPE])
			return true;
	}

	//if (GETKEY[SDL_SCANCODE_ESCAPE]) { return true; }

	return false;
}