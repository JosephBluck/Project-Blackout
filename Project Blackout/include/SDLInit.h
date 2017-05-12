#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "LodePNG.h"

/* THIS FILE IS FOR LOADING AND INITIALISING
SDL2 AND ALL NECESSARY EXTENTIONS, ERRORS ARE
REPORTED VIA IOSTREAM */

bool InitSDL();
bool InitExtensions();
bool InitRenderer(SDL_Window* &window, SDL_Renderer* &renderer);
//bool CheckExit(); //Old exit function, currently deprecated

struct PixelData
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
};