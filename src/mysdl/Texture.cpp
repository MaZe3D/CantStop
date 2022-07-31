#include "Texture.h"
#include "Window.h"
#include "util/sdlcall.h"

int Texture::getWidth()  const { return m_width;  }
int Texture::getHeight() const { return m_height; }
float Texture::getAspect() const { return m_aspect; }

void Texture::draw(const Rect& rect) const {
	if (auto window = m_window.lock())
		window->drawTexture(*this, rect);
	else throw std::runtime_error("window doesn't exist anymore");
}

Texture::Texture(SDL_Texture* texture, const std::weak_ptr<const Window>& window)
	: m_sdlTexture(texture, [](const SDL_Texture* t){ SDL_DestroyTexture(const_cast<SDL_Texture*>(t)); })
	, m_window(window)
{
	SDL_CALL(SDL_QueryTexture(const_cast<SDL_Texture*>(m_sdlTexture.get()), NULL, NULL, &m_width, &m_height));
	m_aspect = static_cast<float>(m_width)/m_height;
}
