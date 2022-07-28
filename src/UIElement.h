#pragma once
#include "SDL2/SDL.h"
#include <list>

struct Rectangle {
	Rectangle(int p_x, int p_y, int p_w, int p_h);
	SDL_Rect m_rect;
};

class UIElement : public Rectangle {
public:
	UIElement(std::list<UIElement*>* UIElement_list, int p_x, int p_y, int p_w, int p_h, SDL_Texture* p_texture);
	virtual ~UIElement();

	void setTexture(SDL_Texture* p_texture);
	void render(SDL_Renderer* p_render);

private:
	std::list<UIElement*>* m_UIElement_list;
	SDL_Texture* m_texture;
};

class InteractableUIElement : public UIElement {
public:
	InteractableUIElement(std::list<UIElement*>* UIElement_list, std::list<InteractableUIElement*>* interactableUIElement_list, int x, int y, int w, int h, SDL_Texture* texture);
	InteractableUIElement(std::list<UIElement*>* UIElement_list, std::list<InteractableUIElement*>* interactableUIElement_list, int x, int y, int w, int h, SDL_Texture* texture, void(*clickedEvent_callback)());
	~InteractableUIElement();

	void (*m_clickedEvent_callback)();

private:
	std::list<InteractableUIElement*>* m_interactableUIElement_list;
};