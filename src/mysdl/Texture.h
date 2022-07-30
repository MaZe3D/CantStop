#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "Rect.h"

class Window;

class Texture {
public:
	int getWidth() const;
	int getHeight() const;

	void draw(const Rect& rect) const;

private:
	friend Window;

	Texture(SDL_Texture* texture, const std::weak_ptr<const Window>& window);

	std::shared_ptr<const SDL_Texture> m_sdlTexture;
	const std::weak_ptr<const Window> m_window;
	int m_width, m_height;
};
