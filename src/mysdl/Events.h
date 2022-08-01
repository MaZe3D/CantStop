#pragma once
#include <SDL2/SDL.h>
#include "Window.h"

class Event {
protected:
	Event(const std::shared_ptr<Window>& window);

	const std::shared_ptr<Window> m_window;
};







// ==================== ClickEvent ====================
class ClickEvent : virtual public Event {
protected:
	ClickEvent(bool subscribeEvent = true);
	virtual ~ClickEvent();

	virtual void subscribe() final;
	virtual void unsubscribe() final;

private:
	friend Window;
	virtual void onClickEvent(const SDL_Event &event) = 0;
};


// LeftClickEvent
class LeftClickEvent : virtual public ClickEvent {
private:
	virtual void onClickEvent(const SDL_Event &event) override final;
	virtual void onLeftClick(int32_t x, int32_t y) = 0;
};







// ==================== WindowEvent ====================
class WindowEvent : virtual public Event {
protected:
	WindowEvent(bool subscribeEvent = true);
	virtual ~WindowEvent();

	virtual void subscribe() final;
	virtual void unsubscribe() final;

private:
	friend Window; // onWindowEvent may ONLY be called from Window
	virtual void onWindowEvent(const SDL_Event &event) = 0;
};


// WindowClosedEvent
class WindowClosedEvent : public WindowEvent {
private:
	virtual void onWindowEvent(const SDL_Event &event) override;
	virtual void onWindowClosed() = 0;
};


// WindowResizedEvent
class WindowResizedEvent : public WindowEvent {
private:
	virtual void onWindowEvent(const SDL_Event &event) override;
	virtual void onWindowResized(int32_t width, int32_t height) = 0;
};







// ==================== KeyboardEvent ====================
class KeyboardEvent : virtual public Event {
protected:
	KeyboardEvent(bool subscribeEvent = true);
	virtual ~KeyboardEvent();

	virtual void subscribe() final;
	virtual void unsubscribe() final;

private:
	friend Window; // onKeyboardEvent may ONLY be called from Window
	virtual void onKeyboardEvent(const SDL_Event &event) = 0;
};


// KeyPressedEvent
class KeyPressedEvent : public KeyboardEvent {
private:
	virtual void onKeyboardEvent(const SDL_Event &event) override;
	virtual void onKeyPressed(const SDL_Keysym& key) = 0;
};
