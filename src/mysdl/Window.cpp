#include <SDL2/SDL_image.h>
#include <algorithm>
#include "Window.h"
#include "util/sdlcall.h"
#include "Events.h"

// static factory, so that there is always a shared_ptr associated and weak_from_this() can be called
std::shared_ptr<Window> Window::create(const std::string& title, int width, int height, bool fullscreen) {
	return std::shared_ptr<Window>(new Window(title, width, height, fullscreen));
}

Window::Window(const std::string& title, int width, int height, bool fullscreen)
	: m_fullscreen(fullscreen)
{
	uint32_t windowFlags = SDL_WINDOW_RESIZABLE;
	if (fullscreen) windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	SDL_Window* window;
	SDL_CALL_INV(window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags));
	m_sdlWindow = std::shared_ptr<SDL_Window>(window, [](SDL_Window* w){ SDL_DestroyWindow(w); });

	SDL_Renderer* renderer;
	SDL_CALL_INV(renderer = SDL_CreateRenderer(m_sdlWindow.get(), -1, 0));
	m_sdlRenderer = std::shared_ptr<SDL_Renderer>(renderer, [](SDL_Renderer* r){ SDL_DestroyRenderer(r); });
}

bool Window::getFullscreen() const {
	return m_fullscreen;
}
void Window::setFullscreen(bool fullscreen) {
	m_fullscreen = fullscreen;
	uint32_t flag = m_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
	SDL_CALL(SDL_SetWindowFullscreen(m_sdlWindow.get(), flag));
}
void Window::toggleFullscreen() {
	setFullscreen(!m_fullscreen);
}

void Window::setWindowIcon(const std::string& path) const {
	SDL_Surface* sdlSurface;
	SDL_CALL_INV(sdlSurface = IMG_Load(path.c_str()));
	SDL_SetWindowIcon(m_sdlWindow.get(), sdlSurface);
	SDL_FreeSurface(sdlSurface);
}

int Window::getWidth () const {
	int width;
	SDL_GetWindowSize(m_sdlWindow.get(), &width, NULL);
	return width;
}

int Window::getHeight() const {
	int height;
	SDL_GetWindowSize(m_sdlWindow.get(), NULL, &height);
	return height;
}

std::shared_ptr<const Texture> Window::loadTexture(const std::string& path) const {
	SDL_Texture* sdlTexture;
	SDL_CALL_INV(sdlTexture = IMG_LoadTexture(m_sdlRenderer.get(), path.c_str()));
	return std::shared_ptr<const Texture>(new Texture(sdlTexture, weak_from_this()));
}

std::shared_ptr<const Texture> Window::createTextureFromSurface(const std::shared_ptr<SDL_Surface>& surface) const {
	SDL_Texture* sdlTexture;
	SDL_CALL_INV(sdlTexture = SDL_CreateTextureFromSurface(m_sdlRenderer.get(), surface.get()));
	return std::shared_ptr<const Texture>(new Texture(sdlTexture, weak_from_this()));
}

void Window::drawTexture(const Texture& texture, const Rect& rect) const {
		SDL_CALL(SDL_RenderCopy(m_sdlRenderer.get(), const_cast<SDL_Texture*>(texture.m_sdlTexture.get()), NULL, &rect.m_sdlRect));
	}

void Window::setDrawColor(uint32_t rgba) const {
	setDrawColor(rgba >> 24, rgba >> 16, rgba >> 8, rgba);
}
void Window::setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const {
	SDL_CALL(SDL_SetRenderDrawColor(m_sdlRenderer.get(), r, g, b, a));
}

void Window::subscribeDrawEvent(DrawEvent* event) {
	if (std::find(m_drawEvents.begin(), m_drawEvents.end(), event) == m_drawEvents.end()) {
		m_drawEvents.push_back(event);
	}
}
void Window::unsubscribeDrawEvent(DrawEvent* event) {
	m_drawEvents.remove(event);
}

void Window::subscribeClickEvent(ClickEvent* event) {
	if (std::find(m_clickEvents.begin(), m_clickEvents.end(), event) == m_clickEvents.end()) {
		m_clickEvents.push_back(event);
	}
}
void Window::unsubscribeClickEvent(ClickEvent* event) {
	m_clickEvents.remove(event);
}

void Window::subscribeWindowEvent(WindowEvent* event) {
	if (std::find(m_windowEvents.begin(), m_windowEvents.end(), event) == m_windowEvents.end()) {
		m_windowEvents.push_back(event);
	}
}
void Window::unsubscribeWindowEvent(WindowEvent* event) {
	m_windowEvents.remove(event);
}

void Window::subscribeKeyboardEvent(KeyboardEvent* event) {
	if (std::find(m_keyboardEvents.begin(), m_keyboardEvents.end(), event) == m_keyboardEvents.end()) {
		m_keyboardEvents.push_back(event);
	}
}
void Window::unsubscribeKeyboardEvent(KeyboardEvent* event) {
	m_keyboardEvents.remove(event);
}

void Window::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			for (auto e : std::list<ClickEvent*>(m_clickEvents))
				e->onClickEvent(event);
			break;
		case SDL_WINDOWEVENT:
			for (auto e : std::list<WindowEvent*>(m_windowEvents))
				e->onWindowEvent(event);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			for (auto e : std::list<KeyboardEvent*>(m_keyboardEvents))
				e->onKeyboardEvent(event);
			break;
		default: break;
		}
	}

	SDL_CALL(SDL_RenderClear(m_sdlRenderer.get()));

	// reverse order -> first subscriber can draw over everyone else
	auto drawEventsReverse = m_drawEvents;
	drawEventsReverse.reverse();
	for (auto e : drawEventsReverse)
		e->onDraw();

	SDL_RenderPresent(m_sdlRenderer.get());
}
