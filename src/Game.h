#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <list>
#include "UIElement.h"

enum class GameState {
	MENU,
	PLAY,
	EXIT
};

class Game{
public:
	Game(char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	~Game();

	void run();

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	GameState m_gameState = GameState::MENU;

	std::list<UIElement*> m_uiElements = std::list<UIElement*>();

	std::list<InteractableUIElement*> m_interactableUIElements = std::list<InteractableUIElement*>();

	void exampleRender();

	void eventHandler();
	void render();

	void init(char* title, int xpos, int ypos, int width, int height, bool fullscreen);
};