#include "Game.h"
#include "util/log.h"

Game::Game(const std::shared_ptr<Window>& window)
	: Event(window)
	, m_window(window)
	, m_font1(Font::create("res/fonts/upheavtt.ttf", 80))
	, m_font2(Font::create("res/fonts/Mx437_Nix8810_M15.ttf", 80))
	, m_menu(window, *this, m_font1, m_font2)
	, m_gameRoundDrawer(window, m_font1)
{
	m_window->setWindowIcon("res/sprites/Dice_Player1_5.png");
	m_window->setDrawColor(0x000000FF);

	onWindowResized(window->getWidth(), window->getHeight());
}

void Game::run() {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	Uint32 frameTime;
	while (m_gameState != GameState::EXIT) {
		frameStart = SDL_GetTicks();

		m_window->handleEvents();
		render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
}

void Game::startNewRound(const std::shared_ptr<GameRound>& round) {
	m_round = round;
	m_gameState = GameState::PLAY;
}

void Game::render() {
	m_window->clear();

	switch (m_gameState) {
	case GameState::MENU:
		m_menu.draw();
		break;
	case GameState::PLAY:
		m_gameRoundDrawer.draw(m_round);
	default:
		break;
	}

	m_window->presentFrame();
}

void Game::onWindowClosed() {
	m_gameState = GameState::EXIT;
}

void Game::onLeftClick(int32_t x, int32_t y) {}

void Game::onWindowResized(int32_t width, int32_t height) {
}
