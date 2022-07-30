#include "TextDrawable.h"

TextDrawable::TextDrawable(const std::shared_ptr<const Font>& font, const std::string& text, const std::shared_ptr<const Window>& window)
	: TextureDrawable(font->renderText(text, window)), font(font), text(text)
{}

void TextDrawable::update(const std::shared_ptr<const Window>& window, bool keepRectDimensions) {
	TextureDrawable::texture = font->renderText(text, window);
	if (!keepRectDimensions)
		TextureDrawable::rect.setDimensions(texture->getWidth(), texture->getHeight());
}
