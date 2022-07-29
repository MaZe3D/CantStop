#include "Texture.h"
#include "util/sdlcall.h"

Texture::Texture(Texture&& source)
	: m_sdlTexture(source.m_sdlTexture),
	m_width(source.m_width),
	m_height(source.m_height)
{
	source.m_sdlTexture = nullptr;
}

Texture::~Texture() {
	if (m_sdlTexture != nullptr)
		SDL_DestroyTexture(const_cast<SDL_Texture*>(m_sdlTexture));
}

int Texture::getWidth()  const { return m_width;  }
int Texture::getHeight() const { return m_height; }

Texture::Texture(SDL_Texture* texture)
	: m_sdlTexture(texture)
{
	SDL_CALL(SDL_QueryTexture(const_cast<SDL_Texture*>(m_sdlTexture), NULL, NULL, &m_width, &m_height));
}
