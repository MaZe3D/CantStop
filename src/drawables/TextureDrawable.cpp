#include "TextureDrawable.h"

TextureDrawable::TextureDrawable(const std::string& path, Window& window)
	: TextureDrawable(window.loadTexture(path))
{}

TextureDrawable::TextureDrawable(const std::string& path, Window& window, const Rect& rect)
	: TextureDrawable(window.loadTexture(path), rect)
{}

TextureDrawable::TextureDrawable(const Texture& texture)
	: TextureDrawable(texture, Rect(0, 0, texture.getWidth(), texture.getHeight()))
{}

TextureDrawable::TextureDrawable(const Texture& texture, const Rect& rect)
	: texture{texture}, rect{rect}
{}

void TextureDrawable::draw() {
	texture.draw(rect);
}
