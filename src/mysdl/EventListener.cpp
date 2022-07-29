#include "EventListener.h"

Event::Event(Window &window) : m_window(window) {}

ClickEvent::ClickEvent(Window &window, bool subscribeEvent) : Event(window) {
    if (subscribeEvent) {
        subscribeClickEvent();
    }
}

ClickEvent::~ClickEvent() {
    unsubscribeClickEvent();
}

void ClickEvent::subscribeClickEvent() {
    m_window.subscribeClickEvent(this);
}

void ClickEvent::unsubscribeClickEvent() {
    m_window.unsubscribeClickEvent(this);
}

WindowEvent::WindowEvent(Window &window, bool subscribeEvent) : Event(window) {
    if (subscribeEvent) {
        subscribeWindowEvent();
    }
}

WindowEvent::~WindowEvent() {
    unsubscribeWindowEvent();
}

void WindowEvent::subscribeWindowEvent() {
    m_window.subscribeWindowEvent(this);
}

void WindowEvent::unsubscribeWindowEvent() {
    m_window.unsubscribeWindowEvent(this);
}