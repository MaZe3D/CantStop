#include "UIElement.h"

UIElement::UIElement(std::list<UIElement*>* UIElement_list, const Rect& rect, const Texture& texture)
	: m_UIElements(UIElement_list), m_rect(rect), m_texture(texture)
{
	m_UIElements->push_back(this);
}

UIElement::~UIElement() {
	m_UIElements->remove(this);
}

//void UIElement::setTexture(const Texture& texture) {
//	m_texture = texture;
//}

void UIElement::render(const Window& window) {
	window.drawTexture(m_texture, m_rect);
}

InteractableUIElement::InteractableUIElement(std::list<UIElement*>* UIElement_list, std::list<InteractableUIElement*>* interactableUIElements, const Rect& rect, const Texture& texture)
	: UIElement(UIElement_list, rect, texture), m_interactableUIElements(interactableUIElements)
{
	m_interactableUIElements->push_back(this);
}

InteractableUIElement::InteractableUIElement(std::list<UIElement*>* UIElement_list, std::list<InteractableUIElement*>* interactableUIElements, const Rect& rect, const Texture& texture, void(*clickedEventCallback)())
	: UIElement(UIElement_list, rect, texture), m_clickedEventCallback(clickedEventCallback), m_interactableUIElements(interactableUIElements)
{
	m_interactableUIElements->push_back(this);
}

InteractableUIElement::~InteractableUIElement() {
	m_interactableUIElements->remove(this);
}
