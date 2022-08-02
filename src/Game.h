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
#include "ux/Menu.h"
#include "ux/GameRoundDrawer.h"
#include "logic/GameRound.h"
#include "util/MersenneTwister.h"

enum class GameState {
	MENU,
	PLAY,
	EXIT
};

class Game : WindowClosedEvent, KeyPressedEvent {
public:
	Game(const std::shared_ptr<Window>& window);
	void run();

	void startNewRound(const std::shared_ptr<GameRound>& round);
	void showMenu();

private:
	const std::shared_ptr<const Font> m_font1;
	const std::shared_ptr<const Font> m_font2;
	Menu m_menu;
	GameRoundDrawer m_gameRoundDrawer;
	GameState m_gameState = GameState::MENU;

	void onWindowClosed() override;
	void onKeyPressed(const SDL_Keysym& key) override;
};
