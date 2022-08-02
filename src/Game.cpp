#include "Game.h"
#include "util/log.h"

Game::Game(const std::shared_ptr<Window>& window)
	: Event(window)
	, WindowClosedEvent(true)
	, KeyPressedEvent(true)
	, m_font1(Font::create("res/fonts/upheavtt.ttf", 80))
	, m_font2(Font::create("res/fonts/Mx437_Nix8810_M15.ttf", 80))
	, m_menu(window, *this, m_font1, m_font2)
	, m_gameRoundDrawer(window, *this, m_font1)
{
	m_window->setWindowIcon("res/sprites/Dice_Player1_5.png");
	m_window->setDrawColor(0x000000FF);
}

void Game::run() {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	m_menu.activate();

	Uint32 frameStart;
	Uint32 frameTime;
	while (m_gameState != GameState::EXIT) {
		frameStart = SDL_GetTicks();

		m_window->handleEvents();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
}

void Game::startNewRound(const std::shared_ptr<GameRound>& round) {
	m_gameState = GameState::PLAY;
	m_gameRoundDrawer.setGameRound(round);
}

void Game::showMenu() {
	m_gameState = GameState::MENU;
	m_menu.restart();
}

void Game::onWindowClosed() {
	m_gameState = GameState::EXIT;
}

void Game::onKeyPressed(const SDL_Keysym& key) {
	if (key.sym == SDLK_F11) m_window->toggleFullscreen();
}
