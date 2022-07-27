#pragma once
#include "SDL2/SDL.h"

class Rectangle {
public:
	Rectangle(int p_x, int p_y, int p_w, int p_h);
	~Rectangle();

protected:
	SDL_Rect m_rect;
};

class UIElement : public Rectangle {
public:
	UIElement(int p_x, int p_y, int p_w, int p_h, SDL_Texture* p_texture);
	~UIElement();

private:
	SDL_Texture* m_texture;
};

class InteractableUIElement : public UIElement {
public:
	InteractableUIElement(int p_x, int p_y, int p_w, int p_h, SDL_Texture* p_texture);
	InteractableUIElement(int p_x, int p_y, int p_w, int p_h, SDL_Texture* p_texture, void(*p_clickedEvent_callback)());
	~InteractableUIElement();
	
	void setClickedEvent_callback(void(*p_callback)());

private:
	void (*m_clickedEvent_callback)();
};