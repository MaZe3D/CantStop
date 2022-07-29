#include "Game.h"
#include "util/log.h"

Game::Game(Window &window) : WindowClosedEvent(window, true), m_window(window), m_texture("res/git-logo.png", m_window) {
	m_window.setDrawColor(0xFFFFFFFF);
}

void Game::render() {
	m_window.clear();
	m_texture.draw();
	m_window.presentFrame();
}

void Game::run() {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	Uint32 frameTime;
	while (m_gameState != GameState::EXIT) {
		frameStart = SDL_GetTicks();

		m_window.handleEvents();
		render();

		frameTime = SDL_GetTicks() - frameStart;
		DEBUG_LOG("Loop time: " << frameTime << "ms");
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
}

void Game::onWindowClosedEvent() {
	m_gameState = GameState::EXIT;
}
