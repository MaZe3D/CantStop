#include "UIElement.h"

Rectangle::Rectangle(int p_x, int p_y, int p_w, int p_h) {
    m_rect.x = p_x;
    m_rect.y = p_y;
    m_rect.w = p_w;
    m_rect.h = p_h;
}

UIElement::UIElement(std::list<UIElement*>* UIElement_list, int p_x, int p_y, int p_w, int p_h, SDL_Texture* p_texture) : Rectangle(p_x, p_y, p_w, p_h), m_UIElement_list(UIElement_list), m_texture(p_texture) {
    m_UIElement_list->push_back(this);
}

UIElement::~UIElement(){
    m_UIElement_list->remove(this);
    SDL_DestroyTexture(m_texture);
}

void UIElement::setTexture(SDL_Texture* p_texture) {  
    if (m_texture != NULL) {
        SDL_DestroyTexture(m_texture);
    }
    m_texture = p_texture;
}

void UIElement::render(SDL_Renderer* p_render) {
    SDL_RenderCopy(p_render, m_texture, NULL, &m_rect);
}

InteractableUIElement::InteractableUIElement(std::list<UIElement*>* UIElement_list, std::list<InteractableUIElement*>* interactableUIElement_list, int x, int y, int w, int h, SDL_Texture* texture) : UIElement(UIElement_list, x, y, w, h, texture), m_interactableUIElement_list(interactableUIElement_list) {
    m_interactableUIElement_list->push_back(this);
}

InteractableUIElement::InteractableUIElement(std::list<UIElement*>* UIElement_list, std::list<InteractableUIElement*>* interactableUIElement_list, int x, int y, int w, int h, SDL_Texture* texture, void(*clickedEvent_callback)()) : UIElement(UIElement_list, x, y, w, h, texture), m_clickedEvent_callback(clickedEvent_callback), m_interactableUIElement_list(interactableUIElement_list) {
    m_interactableUIElement_list->push_back(this);
}

InteractableUIElement::~InteractableUIElement() {
    m_interactableUIElement_list->remove(this);
}