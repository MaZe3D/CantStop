#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <list>
#include "UIElement.h"
#include "mysdl/Window.h"

enum class GameState {
	MENU,
	PLAY,
	EXIT
};

class Game {
public:
	Game();
	~Game();

	void run();

private:
	Window m_window;

	GameState m_gameState = GameState::MENU;

	std::list<UIElement*> m_uiElements = std::list<UIElement*>();

	std::list<InteractableUIElement*> m_interactableUIElements = std::list<InteractableUIElement*>();

	void exampleRender();

	void eventHandler();
	void render();
};
