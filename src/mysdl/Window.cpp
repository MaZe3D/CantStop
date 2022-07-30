#include <SDL2/SDL_image.h>
#include <algorithm>
#include "Window.h"
#include "util/sdlcall.h"
#include "Events.h"

// static factory, so that there is always a shared_ptr associated and weak_from_this() can be called
std::shared_ptr<Window> Window::create(const std::string& title, bool fullscreen, int width, int height) {
	return std::shared_ptr<Window>(new Window(title, fullscreen, width, height));
}

Window::Window(const std::string& title, bool fullscreen, int width, int height) {
	uint32_t windowFlags = SDL_WINDOW_RESIZABLE;
	if (fullscreen) windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	SDL_Window* window;
	SDL_CALL_INV(window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags));
	m_sdlWindow = std::shared_ptr<SDL_Window>(window, [](SDL_Window* w){ SDL_DestroyWindow(w); });

	SDL_Renderer* renderer;
	SDL_CALL_INV(renderer = SDL_CreateRenderer(m_sdlWindow.get(), -1, 0));
	m_sdlRenderer = std::shared_ptr<SDL_Renderer>(renderer, [](SDL_Renderer* r){ SDL_DestroyRenderer(r); });
}

void Window::presentFrame() const {
	SDL_RenderPresent(m_sdlRenderer.get());
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

void Window::clear() const {
	SDL_CALL(SDL_RenderClear(m_sdlRenderer.get()));
}

void Window::subscribeClickEvent(ClickEvent* event) {
	if (std::find(m_clickEvents.begin(), m_clickEvents.end(), event) == m_clickEvents.end()) {
		m_clickEvents.push_back(event);
	}
}

void Window::unsubscribeClickEvent(ClickEvent* event) {
	m_clickEventsToRemove.push_back(event);
}

void Window::subscribeWindowEvent(WindowEvent* event) {
	if (std::find(m_windowEvents.begin(), m_windowEvents.end(), event) == m_windowEvents.end()) {
		m_windowEvents.push_back(event);
	}
}

void Window::unsubscribeWindowEvent(WindowEvent* event) {
	m_windowEventsToRemove.push_back(event);
}

void Window::handleEvents() {
	// can't remove from above lists while iterating through them -> buffer removal
	for (auto e : m_clickEventsToRemove ) m_clickEvents .remove(e);
	for (auto e : m_windowEventsToRemove) m_windowEvents.remove(e);
	m_clickEventsToRemove .clear();
	m_windowEventsToRemove.clear();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			for (auto e : m_clickEvents) e->onClickEvent(event);
			break;
		case SDL_WINDOWEVENT:
			for (auto e : m_windowEvents) e->onWindowEvent(event);
			break;
		default: break;
		}
	}
}
