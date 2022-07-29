#include "Texture.h"
#include "Window.h"
#include "util/sdlcall.h"

int Texture::getWidth()  const { return m_width;  }
int Texture::getHeight() const { return m_height; }

void Texture::draw(const Rect& rect) const {
	m_window.drawTexture(*this, rect);
}

Texture::Texture(SDL_Texture* texture, const Window& window)
	: m_sdlTexture(texture, [](const SDL_Texture* t){ SDL_DestroyTexture(const_cast<SDL_Texture*>(t)); })
	, m_window(window)
{
	SDL_CALL(SDL_QueryTexture(const_cast<SDL_Texture*>(m_sdlTexture.get()), NULL, NULL, &m_width, &m_height));
}
