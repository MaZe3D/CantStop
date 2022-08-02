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

void Window::subscribeLeftClickEvent(LeftClickEvent* event) {
	if (std::find(m_leftClickEvents.begin(), m_leftClickEvents.end(), event) == m_leftClickEvents.end()) {
		m_leftClickEvents.push_back(event);
	}
}
void Window::unsubscribeLeftClickEvent(LeftClickEvent* event) {
	m_leftClickEvents.remove(event);
}

void Window::subscribeWindowClosedEvent(WindowClosedEvent* event) {
	if (std::find(m_windowClosedEvents.begin(), m_windowClosedEvents.end(), event) == m_windowClosedEvents.end()) {
		m_windowClosedEvents.push_back(event);
	}
}
void Window::unsubscribeWindowClosedEvent(WindowClosedEvent* event) {
	m_windowClosedEvents.remove(event);
}

void Window::subscribeWindowResizedEvent(WindowResizedEvent* event) {
	if (std::find(m_windowResizedEvents.begin(), m_windowResizedEvents.end(), event) == m_windowResizedEvents.end()) {
		m_windowResizedEvents.push_back(event);
	}
}
void Window::unsubscribeWindowResizedEvent(WindowResizedEvent* event) {
	m_windowResizedEvents.remove(event);
}

void Window::subscribeKeyPressedEvent(KeyPressedEvent* event) {
	if (std::find(m_keyPressedEvents.begin(), m_keyPressedEvents.end(), event) == m_keyPressedEvents.end()) {
		m_keyPressedEvents.push_back(event);
	}
}
void Window::unsubscribeKeyPressedEvent(KeyPressedEvent* event) {
	m_keyPressedEvents.remove(event);
}

void Window::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				for (auto e : std::list<LeftClickEvent*>(m_leftClickEvents))
					e->onLeftClick(event.button.x, event.button.y);
			}
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
				for (auto e : std::list<WindowClosedEvent*>(m_windowClosedEvents))
					e->onWindowClosed();
			} else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				for (auto e : std::list<WindowResizedEvent*>(m_windowResizedEvents))
					e->onWindowResized(event.window.data1, event.window.data2);
			}
			break;
		case SDL_KEYDOWN:
			for (auto e : std::list<KeyPressedEvent*>(m_keyPressedEvents))
				e->onKeyPressed(event.key.keysym);
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
