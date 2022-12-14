#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#else

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "util/sdlcall.h"
#include "Game.h"

int main(int argc, char** argv) {
	SDL_CALL(SDL_Init(SDL_INIT_VIDEO));
	SDL_CALL(IMG_Init(IMG_INIT_PNG)-IMG_INIT_PNG);
	SDL_CALL(TTF_Init());
	
	Game(Window::create("Can't Stop", 960, 540, false)).run();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}

#endif
