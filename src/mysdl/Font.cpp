#include "Font.h"
#include "util/sdlcall.h"

std::shared_ptr<const Font> Font::create(const std::string& path, int ptSize) {
	return std::shared_ptr<const Font>(new Font(path, ptSize));
}

Font::Font(const std::string& path, int ptSize)
	: path(path), ptSize(ptSize)
{
	TTF_Font* font;
	SDL_CALL_INV(font = TTF_OpenFont(path.c_str(), ptSize));
	m_sdlFont = std::shared_ptr<TTF_Font>(font, [](TTF_Font* f){ TTF_CloseFont(f); });
}

std::shared_ptr<const Font> Font::createDifferentSize(int ptSize) const {
	return Font::create(path, ptSize);
}

std::shared_ptr<const Texture> Font::renderText(const std::string& text, const std::shared_ptr<const Window>& window, uint32_t color) const {
	SDL_Color sdlColor { static_cast<uint8_t>(color >> 24), static_cast<uint8_t>(color >> 16), static_cast<uint8_t>(color >> 8), static_cast<uint8_t>(color) };
	SDL_Surface* rawSurface;
	SDL_CALL_INV(rawSurface = TTF_RenderUTF8_Blended_Wrapped(m_sdlFont.get(), text.c_str(), sdlColor, 0));
	std::shared_ptr<SDL_Surface> surface(rawSurface, [](SDL_Surface* s){ SDL_FreeSurface(s); });

	return window->createTextureFromSurface(surface);
}
