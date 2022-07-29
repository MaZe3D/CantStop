#include "Game.h"
#include "util/log.h"

Game::Game() : m_window("Cant Stop") {
	m_window.setDrawColor(0xFFFFFFFF);
	exampleRender();
}

void Game::eventHandler() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		default:
			break;
		}
	}
}

void Game::render() {
	m_window.clear();
	for (auto& uiElement : m_uiElements) {
		uiElement->render(m_window);
	}
	m_window.presentFrame();
}

Game::~Game() {
	for (auto& uiElement : m_uiElements) {
		delete uiElement;
	}
	for (auto& interactableUIElement : m_interactableUIElements) {
		delete interactableUIElement;
	}
}


void Game::run() {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	Uint32 frameTime;
	while (m_gameState != GameState::EXIT) {
		frameStart = SDL_GetTicks();

		eventHandler();
		render();

		frameTime = SDL_GetTicks() - frameStart;
		DEBUG_LOG("Loop time: " << frameTime << "ms");
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
}

void Game::exampleRender() {
	new UIElement(&m_uiElements, Rect(20, 20, 100, 200), m_window.loadTexture("res/git-logo.png"));
}
