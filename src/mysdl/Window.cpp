#include "Window.h"
#include "util/sdlcall.h"
#include <SDL2/SDL_image.h>

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

const Texture& Window::loadTexture(const std::string& path) {
	SDL_Texture* sdlTexture;
	SDL_CALL_INV(sdlTexture = IMG_LoadTexture(m_sdlRenderer.get(), path.c_str()));
	m_textures.push_back(Texture(sdlTexture, *this));
	return m_textures.back();
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
