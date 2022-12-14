#pragma once
#include "TextureDrawable.h"
#include "mysdl/Font.h"

class TextDrawable : public TextureDrawable {
public:
	TextDrawable(const std::shared_ptr<const Font>& font, const std::string& text, const std::shared_ptr<const Window>& window, uint32_t color = 0xFFFFFFFF);
	void update(const std::shared_ptr<const Window>& window, bool keepRectDimensions = false);

	std::shared_ptr<const Font> font;
	std::string text;
	uint32_t color;
};
