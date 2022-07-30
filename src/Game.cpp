#include "Game.h"
#include "util/log.h"

Game::Game(const std::shared_ptr<Window>& window)
	: Event(window)
	, m_window(window)
	, m_background("res/sprites/MainMenu_Background.png", window)
	, m_menu(window, Font::create("res/fonts/upheavtt.ttf", 80), Font::create("res/fonts/Mx437_Nix8810_M15.ttf", 80))
{
	m_window->setWindowIcon("res/sprites/Dice_Player1_5.png");
	m_window->setDrawColor(0x000000FF);
	m_background.rect.setAnchorModeX(Rect::AnchorMode::CENTER);
	m_background.rect.setAnchorModeY(Rect::AnchorMode::CENTER);

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

void Game::render() {
	m_window->clear();

	m_background.draw();
	m_menu.draw();

	m_window->presentFrame();
}

void Game::onWindowClosed() {
	m_gameState = GameState::EXIT;
}

void Game::onLeftClick(int32_t x, int32_t y) {}

void Game::onWindowResized(int32_t width, int32_t height) {
	float aspect = (float)m_background.texture->getWidth()/m_background.texture->getHeight();
	m_background.rect.setHeightKeepAspect(height, aspect).setPos(width/2, height/2);
}
