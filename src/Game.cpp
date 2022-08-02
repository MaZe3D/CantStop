#include "Game.h"

Game::Game(const std::shared_ptr<Window>& window)
	: Event(window)
	, WindowClosedEvent(true)
	, KeyPressedEvent(true)
	, m_font1(Font::create("res/fonts/upheavtt.ttf", 80))
	, m_font2(Font::create("res/fonts/Mx437_Nix8810_M15.ttf", 80))
	, m_menu(window, m_gameRoundDrawer, m_font1, m_font2)
	, m_gameRoundDrawer(window, m_menu, m_font1)
{
	m_window->setWindowIcon("res/sprites/Dice_Player1_5.png");
	m_window->setDrawColor(0xFF);
}

void Game::run() {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	m_menu.activate();

	Uint32 frameStart;
	Uint32 frameTime;
	while (!m_shouldQuit) {
		frameStart = SDL_GetTicks();

		m_window->handleEvents();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
}

void Game::onWindowClosed() {
	m_shouldQuit = true;
}

void Game::onKeyPressed(const SDL_Keysym& key) {
	if (key.sym == SDLK_F11)
		m_window->toggleFullscreen();
}
