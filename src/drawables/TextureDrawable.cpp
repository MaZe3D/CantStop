#include "TextureDrawable.h"

TextureDrawable::TextureDrawable(const std::string& path, const std::shared_ptr<Window>& window)
	: TextureDrawable(window->loadTexture(path))
{}

TextureDrawable::TextureDrawable(const std::string& path, const std::shared_ptr<Window>& window, const Rect& rect)
	: TextureDrawable(window->loadTexture(path), rect)
{}

TextureDrawable::TextureDrawable(const std::shared_ptr<const Texture>& texture)
	: TextureDrawable(texture, Rect(0, 0, texture->getWidth(), texture->getHeight()))
{}

TextureDrawable::TextureDrawable(const std::shared_ptr<const Texture>& texture, const Rect& rect)
	: rect{rect}, m_texture{texture}
{
	if (!texture) throw std::runtime_error("TextureDrawable::TextureDrawable() - texture can't ben nullptr");
}

const std::shared_ptr<const Texture>& TextureDrawable::getTexture() {
	return m_texture;
}

void TextureDrawable::setTexture(const std::shared_ptr<const Texture>& texture) {
	if (!texture) throw std::runtime_error("TextureDrawable::setTexture() - texture can't ben nullptr");
	m_texture = texture;
}

void TextureDrawable::draw() {
	m_texture->draw(rect);
}
