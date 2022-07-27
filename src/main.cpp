#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#else

#include <doctest.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Game.h"

int main(int argc, char** argv) 
{
	Game * game = new Game();
	game->run();
	return 0;	
}

#endif

TEST_CASE("sanity check") {
	REQUIRE(1 < 2);
	CHECK('a' != 'b');
	WARN('a'+1 == 'b');
}
