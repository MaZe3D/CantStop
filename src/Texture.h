#pragma once
#include <SDL2/SDL.h>
#include "Rect.h"

class Window;

class Texture final {
public:
	Texture(Texture&& source);
	~Texture();

	int getWidth() const;
	int getHeight() const;

private:
	friend Window;

	Texture(const Texture&) = delete;
	Texture &operator=(const Texture&) = delete;
	Texture(SDL_Texture* texture);

	const SDL_Texture* m_sdlTexture;
	int m_width, m_height;
};
