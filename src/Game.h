#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <list>
#include "mysdl/Window.h"
#include "drawables/TextureDrawable.h"
#include "mysdl/EventListener.h"

enum class GameState {
	MENU,
	PLAY,
	EXIT
};

class Game : public WindowClosedEvent {
public:
	Game(const std::shared_ptr<Window>& window);
	void run();

private:
	const std::shared_ptr<Window> m_window;
	TextureDrawable m_texture;
	GameState m_gameState = GameState::MENU;

	void render();
	void onWindowClosedEvent() override;
};
