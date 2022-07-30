#pragma once
#include <SDL2/SDL.h>
#include "Window.h"

class Event {
public:
	Event(const std::shared_ptr<Window>& window);
	
protected:
	std::shared_ptr<Window> m_window;
};

class ClickEvent : public Event {
public:
	ClickEvent(const std::shared_ptr<Window>& window, bool subscribeEvent = true);
	virtual ~ClickEvent();

	void subscribeClickEvent();
	void unsubscribeClickEvent();
	
	virtual void onClick(const SDL_Event &event) = 0;
};

class WindowEvent : public Event {
public:
	WindowEvent(const std::shared_ptr<Window>& window, bool subscribeEvent = true);
	virtual ~WindowEvent();

	void subscribeWindowEvent();
	void unsubscribeWindowEvent();
	
	virtual void onWindowEvent(const SDL_Event &event) = 0;
};

class WindowClosedEvent : public WindowEvent {
public:
	WindowClosedEvent(const std::shared_ptr<Window>& window, bool subscribeEvent = true);
	void onWindowEvent(const SDL_Event &event) final;
	virtual void onWindowClosedEvent() = 0;
};
