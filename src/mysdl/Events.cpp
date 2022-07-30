#include "Events.h"

Event::Event(const std::shared_ptr<Window>& window)
	: m_window(window)
{}







// ==================== ClickEvent ====================
ClickEvent::ClickEvent(bool sub) {
	if (sub) subscribe();
}
ClickEvent::~ClickEvent() {
	unsubscribe();
}

void ClickEvent::  subscribe() { m_window->  subscribeClickEvent(this); }
void ClickEvent::unsubscribe() { m_window->unsubscribeClickEvent(this); }


// LeftClickEvent
void LeftClickEvent::onClickEvent(const SDL_Event &event) {
	if (event.button.button != SDL_BUTTON_LEFT) return;
	onLeftClick(event.button.x, event.button.y);
}







// ==================== WindowEvent ====================
WindowEvent::WindowEvent(bool sub) {
	if (sub) subscribe();
}
WindowEvent::~WindowEvent() {
	unsubscribe();
}

void WindowEvent::  subscribe() { m_window->  subscribeWindowEvent(this); }
void WindowEvent::unsubscribe() { m_window->unsubscribeWindowEvent(this); }

// WindowClosedEvent
void WindowClosedEvent::onWindowEvent(const SDL_Event& event) {
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		onWindowClosed();
}

// WindowResizedEvent
void WindowResizedEvent::onWindowEvent(const SDL_Event& event) {
	if (event.window.event == SDL_WINDOWEVENT_RESIZED)
		onWindowResized(event.window.data1, event.window.data2);
}
