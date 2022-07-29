#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "util/sdlcall.h"
#include "Texture.h"
#include "Rect.h"

class Window {
public:
	Window(const Window&) = delete;
	Window &operator=(const Window&) = delete;

	Window(const std::string& title, bool fullscreen = false, int width = 800, int height = 500);
	~Window();

	void presentFrame() const;

	const Texture& loadTexture(const std::string& path);

	void drawTexture(const Texture& texture, const Rect& rect) const;

	void setDrawColor(uint32_t rgba) const;
	void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) const;

	void clear() const;

	void drawRect() const;
	void fillRect() const;

private:
	SDL_Window* m_sdlWindow;
	SDL_Renderer* m_sdlRenderer;
	std::vector<Texture> m_textures;
};
