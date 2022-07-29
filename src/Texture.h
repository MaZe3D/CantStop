#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "Rect.h"

class Window;

class Texture final {
public:
	int getWidth() const;
	int getHeight() const;

private:
	friend Window;

	Texture(SDL_Texture* texture);

	std::shared_ptr<const SDL_Texture> m_sdlTexture;
	int m_width, m_height;
};
