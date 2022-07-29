#pragma once
#include <SDL2/SDL.h>
#include "Window.h"

class Event {
public: 
	Event(Window &window);
	
protected:
	Window &m_window;
};

class ClickEvent : public Event {
public:
	ClickEvent(Window &window, bool subscribeEvent = true);
	~ClickEvent();

	void subscribeClickEvent();
	void unsubscribeClickEvent();
	
	virtual void onClick(const SDL_Event &event) = 0;
};

class WindowEvent : public Event {
public:
	WindowEvent(Window &window, bool subscribeEvent = true);
	~WindowEvent();

	void subscribeWindowEvent();
	void unsubscribeWindowEvent();
	
	virtual void onWindowEvent(const SDL_Event &event) = 0;
};

class WindowClosedEvent : public WindowEvent {
public:
	WindowClosedEvent(Window &window, bool subscribeEvent = true);	
	void onWindowEvent(const SDL_Event &event) final;
	virtual void onWindowClosedEvent() = 0;
};