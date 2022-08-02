#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <list>
#include "Texture.h"
#include "Rect.h"

class DrawEvent;
class LeftClickEvent;
class WindowClosedEvent;
class WindowResizedEvent;
class KeyPressedEvent;

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

	void   subscribeLeftClickEvent(LeftClickEvent* event);
	void unsubscribeLeftClickEvent(LeftClickEvent* event);

	void   subscribeWindowClosedEvent(WindowClosedEvent* event);
	void unsubscribeWindowClosedEvent(WindowClosedEvent* event);

	void   subscribeWindowResizedEvent(WindowResizedEvent* event);
	void unsubscribeWindowResizedEvent(WindowResizedEvent* event);

	void   subscribeKeyPressedEvent(KeyPressedEvent* event);
	void unsubscribeKeyPressedEvent(KeyPressedEvent* event);

private:
	Window(const std::string& title, int width, int height, bool fullscreen);

	bool m_fullscreen;

	std::list<DrawEvent*> m_drawEvents;
	std::list<LeftClickEvent*> m_leftClickEvents;
	std::list<WindowClosedEvent*> m_windowClosedEvents;
	std::list<WindowResizedEvent*> m_windowResizedEvents;
	std::list<KeyPressedEvent*> m_keyPressedEvents;
	
	std::shared_ptr<SDL_Window> m_sdlWindow;
	std::shared_ptr<SDL_Renderer> m_sdlRenderer;
};
