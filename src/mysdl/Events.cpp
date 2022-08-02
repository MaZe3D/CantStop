#include "Events.h"

Event::Event(const std::shared_ptr<Window>& window)
	: m_window(window)
{}







// ==================== DrawEvent ====================
DrawEvent::DrawEvent(bool sub) {
	if (sub) subscribe();
}
DrawEvent::~DrawEvent() {
	unsubscribe();
}

void DrawEvent::  subscribe() { m_window->  subscribeDrawEvent(this); }
void DrawEvent::unsubscribe() { m_window->unsubscribeDrawEvent(this); }







// ==================== LeftClickEvent ====================
LeftClickEvent::LeftClickEvent(bool sub) {
	if (sub) subscribe();
}
LeftClickEvent::~LeftClickEvent() {
	unsubscribe();
}

void LeftClickEvent::  subscribe() { m_window->  subscribeLeftClickEvent(this); }
void LeftClickEvent::unsubscribe() { m_window->unsubscribeLeftClickEvent(this); }







// ==================== WindowClosedEvent ====================
WindowClosedEvent::WindowClosedEvent(bool sub) {
	if (sub) subscribe();
}
WindowClosedEvent::~WindowClosedEvent() {
	unsubscribe();
}

void WindowClosedEvent::  subscribe() { m_window->  subscribeWindowClosedEvent(this); }
void WindowClosedEvent::unsubscribe() { m_window->unsubscribeWindowClosedEvent(this); }







// ==================== WindowResizedEvent ====================
WindowResizedEvent::WindowResizedEvent(bool sub) {
	if (sub) subscribe();
}
WindowResizedEvent::~WindowResizedEvent() {
	unsubscribe();
}

void WindowResizedEvent::  subscribe() { m_window->  subscribeWindowResizedEvent(this); }
void WindowResizedEvent::unsubscribe() { m_window->unsubscribeWindowResizedEvent(this); }






// ==================== KeyPressedEvent ====================
KeyPressedEvent::KeyPressedEvent(bool sub) {
	if (sub) subscribe();
}
KeyPressedEvent::~KeyPressedEvent() {
	unsubscribe();
}

void KeyPressedEvent::  subscribe() { m_window->  subscribeKeyPressedEvent(this); }
void KeyPressedEvent::unsubscribe() { m_window->unsubscribeKeyPressedEvent(this); }
