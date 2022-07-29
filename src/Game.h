#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <list>
#include "mysdl/Window.h"

enum class GameState {
	MENU,
	PLAY,
	EXIT
};

class Game {
public:
	Game();

	void run();

private:
	Window m_window;

	GameState m_gameState = GameState::MENU;

	void eventHandler();
	void render();
};
