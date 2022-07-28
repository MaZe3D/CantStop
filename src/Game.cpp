#include "Game.h"
#include "util/log.h"

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
	SDL_RenderClear(m_renderer);
	for (auto& uiElement : m_uiElements) {
		uiElement->render(m_renderer);
	}
	SDL_RenderPresent(m_renderer);
}

void Game::init(char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if(fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		DEBUG_LOG("Subsystems initialized");
		m_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if(m_window) {
			DEBUG_LOG("Window created");
			m_renderer = SDL_CreateRenderer(m_window, -1, 0);
			if(m_renderer) {
				DEBUG_LOG("Renderer created");
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				m_gameState = GameState::MENU;
			} else {
				DEBUG_LOG("Renderer failed to create!");
				m_gameState = GameState::EXIT;
			}
		} else {
			DEBUG_LOG("Window failed to create!");
			m_gameState = GameState::EXIT;
		}
	}
	IMG_Init(IMG_INIT_PNG);
	exampleRender();
}

Game::~Game() {
	for (auto& uiElement : m_uiElements) {
		delete uiElement;
	}
	for (auto& interactableUIElement : m_interactableUIElements) {
		delete interactableUIElement;
	}
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

Game::Game(char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	const int minimalWindowWidth = 800;
	const int minimalWindowHeight = 600;
	if (width < minimalWindowWidth) {
		throw std::invalid_argument("Width must be greater than " + std::to_string(minimalWindowWidth) + "px");
	}

	if(height < minimalWindowHeight) {
		throw std::invalid_argument("Height must be greater than " + std::to_string(minimalWindowHeight) + "px");
	}

	init(title, xpos, ypos, width, height, fullscreen);
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
	new UIElement(&m_uiElements, 20, 20, 100, 200, IMG_LoadTexture(m_renderer, "res/git-logo.png"));
}
