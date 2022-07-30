#include "EventListener.h"

Event::Event(const std::shared_ptr<Window>& window) : m_window(window) {}

ClickEvent::ClickEvent(const std::shared_ptr<Window>& window, bool subscribeEvent) : Event(window) {
    if (subscribeEvent) {
        subscribeClickEvent();
    }
}

ClickEvent::~ClickEvent() {
    unsubscribeClickEvent();
}

void ClickEvent::subscribeClickEvent() {
    m_window->subscribeClickEvent(this);
}

void ClickEvent::unsubscribeClickEvent() {
    m_window->unsubscribeClickEvent(this);
}

WindowEvent::WindowEvent(const std::shared_ptr<Window>& window, bool subscribeEvent) : Event(window) {
    if (subscribeEvent) {
        subscribeWindowEvent();
    }
}

WindowEvent::~WindowEvent() {
    unsubscribeWindowEvent();
}

void WindowEvent::subscribeWindowEvent() {
    m_window->subscribeWindowEvent(this);
}

void WindowEvent::unsubscribeWindowEvent() {
    m_window->unsubscribeWindowEvent(this);
}
