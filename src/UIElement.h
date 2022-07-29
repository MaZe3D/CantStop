#pragma once
#include "SDL2/SDL.h"
#include <list>
#include "mysdl/Texture.h"
#include "mysdl/Window.h"

class UIElement {
public:
	UIElement(std::list<UIElement*>* UIElement_list, const Rect& rect, const Texture& texture);
	virtual ~UIElement();

	//void setTexture(const Texture& texture);
	void render(const Window& window);

private:
	std::list<UIElement*>* m_UIElements;
	Rect m_rect;
	const Texture& m_texture;
};

class InteractableUIElement : public UIElement {
public:
	InteractableUIElement(std::list<UIElement*>* UIElement_list, std::list<InteractableUIElement*>* interactableUIElements, const Rect& rect, const Texture& texture);
	InteractableUIElement(std::list<UIElement*>* UIElement_list, std::list<InteractableUIElement*>* interactableUIElements, const Rect& rect, const Texture& texture, void(*clickedEventCallback)());
	~InteractableUIElement();

	void (*m_clickedEventCallback)();

private:
	std::list<InteractableUIElement*>* m_interactableUIElements;
};
