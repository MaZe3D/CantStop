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

	const std::shared_ptr<const Texture>& getTexture();
	void setTexture(const std::shared_ptr<const Texture>& texture);

	TextureDrawable& setWidthKeepAspect(int width);
	TextureDrawable& setHeightKeepAspect(int height);

	void draw();

	Rect rect;

private:
	std::shared_ptr<const Texture> m_texture;
};
