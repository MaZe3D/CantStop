#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <list>
#include "Texture.h"
#include "Rect.h"

class ClickEvent;
class WindowEvent;
class KeyboardEvent;

class Window : public std::enable_shared_from_this<Window> {
public:
	static std::shared_ptr<Window> create(const std::string& title, bool fullscreen = false, int width = 800, int height = 500);

	void setWindowIcon(const std::string& path) const;

	int getWidth() const;
	int getHeight() const;

	void presentFrame() const;

	std::shared_ptr<const Texture> loadTexture(const std::string& path) const;

	std::shared_ptr<const Texture> createTextureFromSurface(const std::shared_ptr<SDL_Surface>& surface) const;

	void drawTexture(const Texture& texture, const Rect& rect) const;

	void setDrawColor(uint32_t rgba) const;
	void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) const;

	void clear() const;

	void drawRect() const;
	void fillRect() const;

	void handleEvents();

	void subscribeClickEvent(ClickEvent* event);
	void unsubscribeClickEvent(ClickEvent* event);

	void subscribeWindowEvent(WindowEvent* event);
	void unsubscribeWindowEvent(WindowEvent* event);

	void subscribeKeyboardEvent(KeyboardEvent* event);
	void unsubscribeKeyboardEvent(KeyboardEvent* event);

private:
	Window(const std::string& title, bool fullscreen, int width, int height);

	std::list<ClickEvent*> m_clickEvents;
	std::list<WindowEvent*> m_windowEvents;
	std::list<KeyboardEvent*> m_keyboardEvents;
	
	std::shared_ptr<SDL_Window> m_sdlWindow;
	std::shared_ptr<SDL_Renderer> m_sdlRenderer;
};
