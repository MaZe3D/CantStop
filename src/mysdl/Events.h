#pragma once
#include <SDL2/SDL.h>
#include "Window.h"

class Event {
protected:
	Event(const std::shared_ptr<Window>& window);

	const std::shared_ptr<Window> m_window;
};







// ==================== DrawEvent ====================
class DrawEvent : virtual public Event {
protected:
	DrawEvent(bool subscribeEvent = false);
	virtual ~DrawEvent();

	virtual void subscribe() final;
	virtual void unsubscribe() final;

private:
	friend Window;
	virtual void onDraw() = 0;
};







// ==================== LeftClickEvent ====================
class LeftClickEvent : virtual public Event {
protected:
	LeftClickEvent(bool subscribeEvent = false);
	virtual ~LeftClickEvent();

	virtual void subscribe() final;
	virtual void unsubscribe() final;

private:
	friend Window; // onLeftClick may ONLY be called from Window
	virtual void onLeftClick(int32_t x, int32_t y) = 0;
};







// ==================== WindowClosedEvent ====================
class WindowClosedEvent : virtual public Event {
protected:
	WindowClosedEvent(bool subscribeEvent = false);
	virtual ~WindowClosedEvent();

	virtual void subscribe() final;
	virtual void unsubscribe() final;

private:
	friend Window; // onWindowClosed may ONLY be called from Window
	virtual void onWindowClosed() = 0;
};







// ==================== WindoResizedwEvent ====================
class WindowResizedEvent : virtual public Event {
protected:
	WindowResizedEvent(bool subscribeEvent = false);
	virtual ~WindowResizedEvent();

	virtual void subscribe() final;
	virtual void unsubscribe() final;

private:
	friend Window; // onWindowResized may ONLY be called from Window
	virtual void onWindowResized(int32_t width, int32_t height) = 0;
};







// ==================== KeyPressedEvent ====================
class KeyPressedEvent : virtual public Event {
protected:
	KeyPressedEvent(bool subscribeEvent = false);
	virtual ~KeyPressedEvent();

	virtual void subscribe() final;
	virtual void unsubscribe() final;

private:
	friend Window; // onKeyPressed may ONLY be called from Window
	virtual void onKeyPressed(const SDL_Keysym& key) = 0;
};
