#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

enum class GameState {
	MENU,
	PLAY,
	EXIT
};

class Game {
public:
	Game(char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	~Game();

	void run();

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	GameState m_gameState = GameState::MENU;

	void eventHandler();
	void render();

	void init(char* title, int xpos, int ypos, int width, int height, bool fullscreen);
};
