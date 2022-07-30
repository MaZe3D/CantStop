#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <list>
#include "Texture.h"
#include "Rect.h"

class ClickEvent;
class WindowEvent;

class Window : public std::enable_shared_from_this<Window> {
public:
	static std::shared_ptr<Window> create(const std::string& title, bool fullscreen = false, int width = 800, int height = 500);

	void presentFrame() const;

	std::shared_ptr<const Texture> loadTexture(const std::string& path) const;

	std::shared_ptr<const Texture> createTextureFromSurface(const std::shared_ptr<SDL_Surface>& surface) const;

	void drawTexture(const Texture& texture, const Rect& rect) const;

	void setDrawColor(uint32_t rgba) const;
	void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) const;

	void clear() const;

	void drawRect() const;
	void fillRect() const;

	void handleEvents() const;

	void subscribeClickEvent(ClickEvent* listener);
	void unsubscribeClickEvent(ClickEvent* listener);

	void subscribeWindowEvent(WindowEvent* listener);
	void unsubscribeWindowEvent(WindowEvent*listener);


private:
	Window(const std::string& title, bool fullscreen, int width, int height);

	std::list<ClickEvent*> m_clickEventSubscribers;
	std::list<WindowEvent*> m_windowEventSubscribers;
	
	std::shared_ptr<SDL_Window> m_sdlWindow;
	std::shared_ptr<SDL_Renderer> m_sdlRenderer;
};
