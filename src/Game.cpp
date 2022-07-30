#include "Game.h"
#include "util/log.h"

Game::Game(const std::shared_ptr<Window>& window)
	: Event(window)
	, m_window(window)
	, m_texture("res/git-logo.png", window)
	, m_text(Font::create("res/beyond-wonderland.regular.ttf", 80), "this is a test text\n...", window)
{
	m_window->setDrawColor(0x000000FF);
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
	//m_text.rect.setPosX(m_text.rect.getPosX()+1);

	m_window->clear();
	m_texture.draw();
	m_text.draw();
	m_window->presentFrame();
}

void Game::onWindowClosed() {
	m_gameState = GameState::EXIT;
}

static uint8_t clickCount = 7;
void Game::onLeftClick(int32_t x, int32_t y) {
	if (--clickCount == 0) ClickEvent::unsubscribe();
	m_text.text += " :D";
	m_text.color = rand() << 16 | rand() | 0x70;
	m_text.update(m_window);
}

void Game::onWindowResized(int32_t width, int32_t height) {
	if (clickCount == 0) ClickEvent::subscribe();
	m_text.text = "resized to " + std::to_string(width) + "x" + std::to_string(height);
	m_text.update(m_window);
}
