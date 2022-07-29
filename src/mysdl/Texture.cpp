#include "Texture.h"
#include "util/sdlcall.h"

int Texture::getWidth()  const { return m_width;  }
int Texture::getHeight() const { return m_height; }

Texture::Texture(SDL_Texture* texture)
	: m_sdlTexture(texture, [](const SDL_Texture* t){ SDL_DestroyTexture(const_cast<SDL_Texture*>(t)); })
{
	SDL_CALL(SDL_QueryTexture(const_cast<SDL_Texture*>(m_sdlTexture.get()), NULL, NULL, &m_width, &m_height));
}
