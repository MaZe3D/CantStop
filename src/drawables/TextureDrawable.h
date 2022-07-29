#pragma once
#include "Drawable.h"
#include "mysdl/Texture.h"
#include "mysdl/Rect.h"

class TextureDrawable : public Drawable {
public:
	TextureDrawable(const std::string& path, Window& window);
	TextureDrawable(const std::string& path, Window& window, const Rect& rect);
	TextureDrawable(const Texture& texture);
	TextureDrawable(const Texture& texture, const Rect& rect);
	void draw();

	Texture texture;
	Rect rect;
};
