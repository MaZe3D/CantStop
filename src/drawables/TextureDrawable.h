#pragma once
#include "Drawable.h"
#include "mysdl/Texture.h"
#include "mysdl/Rect.h"

class TextureDrawable : public Drawable {
public:
	TextureDrawable(const std::string& path, const std::shared_ptr<Window>& window);
	TextureDrawable(const std::string& path, const std::shared_ptr<Window>& window, const Rect& rect);
	TextureDrawable(const std::shared_ptr<const Texture>& texture);
	TextureDrawable(const std::shared_ptr<const Texture>& texture, const Rect& rect);
	void draw();

	std::shared_ptr<const Texture> texture;
	Rect rect;
};
