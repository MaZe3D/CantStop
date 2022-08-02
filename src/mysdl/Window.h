#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <list>
#include "Texture.h"
#include "Rect.h"

class DrawEvent;
class ClickEvent;
class WindowEvent;
class KeyboardEvent;

class Window : public std::enable_shared_from_this<Window> {
public:
	static std::shared_ptr<Window> create(const std::string& title, int width = 800, int height = 600, bool fullscreen = false);

	bool getFullscreen() const;
	void setFullscreen(bool fullscreen);
	void toggleFullscreen();

	void setWindowIcon(const std::string& path) const;

	int getWidth() const;
	int getHeight() const;

	std::shared_ptr<const Texture> loadTexture(const std::string& path) const;

	std::shared_ptr<const Texture> createTextureFromSurface(const std::shared_ptr<SDL_Surface>& surface) const;

	void drawTexture(const Texture& texture, const Rect& rect) const;

	void setDrawColor(uint32_t rgba) const;
	void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) const;

	void handleEvents();

	void   subscribeDrawEvent(DrawEvent* event);
	void unsubscribeDrawEvent(DrawEvent* event);

	void   subscribeClickEvent(ClickEvent* event);
	void unsubscribeClickEvent(ClickEvent* event);

	void   subscribeWindowEvent(WindowEvent* event);
	void unsubscribeWindowEvent(WindowEvent* event);

	void   subscribeKeyboardEvent(KeyboardEvent* event);
	void unsubscribeKeyboardEvent(KeyboardEvent* event);

private:
	Window(const std::string& title, int width, int height, bool fullscreen);

	bool m_fullscreen;

	std::list<DrawEvent*> m_drawEvents;
	std::list<ClickEvent*> m_clickEvents;
	std::list<WindowEvent*> m_windowEvents;
	std::list<KeyboardEvent*> m_keyboardEvents;
	
	std::shared_ptr<SDL_Window> m_sdlWindow;
	std::shared_ptr<SDL_Renderer> m_sdlRenderer;
};
