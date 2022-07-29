#pragma once
#include <SDL2/SDL.h>

class Window;

class Rect {
public:
	enum class AnchorMode { LEFT, RIGHT, TOP, BOTTOM, CENTER };

	Rect(int posX, int posY, int width, int height, AnchorMode anchorModeX = AnchorMode::LEFT, AnchorMode anchorModeY = AnchorMode::TOP);

	int getPosX() const;
	int getPosY() const;
	int getWidth() const;
	int getHeight() const;

	int getLeft() const;
	int getTop() const;
	int getRight() const;
	int getBottom() const;

	Rect& setPos(int x, int y);
	Rect& setPosX(int x);
	Rect& setPosY(int y);

	Rect& setDimensions (int width, int height);
	Rect& setWidth (int width);
	Rect& setHeight(int height);

	Rect& setWidthKeepAspect (int width);
	Rect& setHeightKeepAspect(int height);
	Rect& setWidthKeepAspect (int width,  float ascpect);
	Rect& setHeightKeepAspect(int height, float ascpect);

	Rect& setAnchorModeX(AnchorMode anchorModeX);
	Rect& setAnchorModeY(AnchorMode anchorModeY);

private:
	friend Window;

	void updateX();
	void updateY();

	int m_anchorPosX, m_anchorPosY;
	SDL_Rect m_sdlRect;
	AnchorMode m_anchorModeX, m_anchorModeY;
};
