#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <list>
#include "mysdl/Window.h"
#include "drawables/TextureDrawable.h"
#include "drawables/TextDrawable.h"
#include "mysdl/Events.h"
#include "Menu.h"
#include "GameRoundDrawer.h"

enum class GameState {
	MENU,
	PLAY,
	EXIT
};

class Game : WindowClosedEvent, LeftClickEvent, WindowResizedEvent {
public:
	Game(const std::shared_ptr<Window>& window);
	void run();

	void startNewRound();

private:
	const std::shared_ptr<Window> m_window;
	const std::shared_ptr<const Font> m_font1;
	const std::shared_ptr<const Font> m_font2;
	Menu m_menu;
	GameRoundDrawer m_gameRoundDrawer;

	GameState m_gameState = GameState::MENU;

	void render();
	void onWindowClosed() override;
	void onLeftClick(int32_t x, int32_t y) override;
	void onWindowResized(int32_t width, int32_t height) override;
};
