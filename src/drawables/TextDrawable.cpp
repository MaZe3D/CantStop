#include "TextDrawable.h"

TextDrawable::TextDrawable(const std::shared_ptr<const Font>& font, const std::string& text, const std::shared_ptr<const Window>& window, uint32_t color)
	: TextureDrawable(font->renderText(text, window, color)), font(font), text(text), color(color)
{}

void TextDrawable::update(const std::shared_ptr<const Window>& window, bool keepRectDimensions) {
	TextureDrawable::setTexture(font->renderText(text, window, color));
	if (!keepRectDimensions)
		TextureDrawable::rect.setDimensions(TextureDrawable::getTexture()->getWidth(), TextureDrawable::getTexture()->getHeight());
}
