#pragma once
#include <string>
#include <memory>
#include <SDL2/SDL_ttf.h>
#include "texture.h"
#include "Window.h"

class Font {
public:
	static std::shared_ptr<const Font> create(const std::string& path, int ptSize);

	const std::string path;
	const int ptSize;

	std::shared_ptr<const Font> createDifferentSize(int ptSize) const;
	std::shared_ptr<const Texture> renderText(const std::string& text, const std::shared_ptr<const Window>& window) const;

private:
	std::shared_ptr<TTF_Font> m_sdlFont;

	Font(const std::string& path, int ptSize);
};
