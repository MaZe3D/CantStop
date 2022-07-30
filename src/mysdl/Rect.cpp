#include "Rect.h"
#include <stdexcept>
#include "doctest.h"

Rect::Rect(int posX, int posY, int width, int height, AnchorMode anchorModeX, AnchorMode anchorModeY)
	: m_anchorPosX{posX}, m_anchorPosY{posY},
	  m_sdlRect{0, 0, width, height},
	  m_anchorModeX{anchorModeX}, m_anchorModeY{anchorModeY}
{
	updateX();
	updateY();
}

int Rect::getPosX()   const { return m_anchorPosX; }
int Rect::getPosY()   const { return m_anchorPosY; }
int Rect::getWidth()  const { return m_sdlRect.w; }
int Rect::getHeight() const { return m_sdlRect.h; }

int Rect::getLeft()   const { return m_sdlRect.x; }
int Rect::getTop()    const { return m_sdlRect.y; }
int Rect::getRight()  const { return m_sdlRect.x + m_sdlRect.w; }
int Rect::getBottom() const { return m_sdlRect.y + m_sdlRect.h; }

Rect& Rect::setPos(int x, int y) { setPosX(x); setPosY(y); return *this; }
Rect& Rect::setPosX(int x) { m_anchorPosX = x; updateX(); return *this; }
Rect& Rect::setPosY(int y) { m_anchorPosY = y; updateY(); return *this; }

Rect& Rect::setDimensions (int width, int height) { setWidth(width); setHeight(height); return *this; }
Rect& Rect::setWidth (int width)  { m_sdlRect.w = width;  updateX(); return *this; }
Rect& Rect::setHeight(int height) { m_sdlRect.h = height; updateY(); return *this; }

Rect& Rect::setWidthKeepAspect (int width)  { return setWidthKeepAspect (width,  (float)m_sdlRect.w/m_sdlRect.h); }
Rect& Rect::setHeightKeepAspect(int height) { return setHeightKeepAspect(height, (float)m_sdlRect.w/m_sdlRect.h); }
Rect& Rect::setWidthKeepAspect (int width,  float aspect) { m_sdlRect.w = width;  m_sdlRect.h = width/aspect;  updateX(); updateY(); return *this; }
Rect& Rect::setHeightKeepAspect(int height, float aspect) { m_sdlRect.h = height; m_sdlRect.w = height*aspect; updateX(); updateY(); return *this; }

Rect& Rect::setAnchorModeX(AnchorMode anchorModeX) { m_anchorModeX = anchorModeX; updateX(); return *this; }
Rect& Rect::setAnchorModeY(AnchorMode anchorModeY) { m_anchorModeY = anchorModeY; updateY(); return *this; }

bool Rect::containsPoint(int x, int y) {
	return (getLeft() <= x && x <= getRight() && getTop() <= y && y <= getBottom());
}

void Rect::updateX() {
	if (m_sdlRect.w < 0) throw std::runtime_error("Rect - values out of range");
	m_sdlRect.x = m_anchorPosX;
	switch (m_anchorModeX) {
		case AnchorMode::LEFT: break;
		case AnchorMode::CENTER: m_sdlRect.x -= m_sdlRect.w/2; break;
		case AnchorMode::RIGHT:  m_sdlRect.x -= m_sdlRect.w;   break;
		default: throw std::runtime_error("Rect - invalid anchor mode");
	}
	if (m_sdlRect.x > m_anchorPosX) throw std::runtime_error("Rect - values out of range");
}

void Rect::updateY() {
	if (m_sdlRect.h < 0) throw std::runtime_error("Rect - values out of range");
	m_sdlRect.y = m_anchorPosY;
	switch (m_anchorModeY) {
		case AnchorMode::TOP: break;
		case AnchorMode::CENTER: m_sdlRect.y -= m_sdlRect.h/2; break;
		case AnchorMode::BOTTOM: m_sdlRect.y -= m_sdlRect.h;   break;
		default: throw std::runtime_error("Rect - invalid anchor mode");
	}
	if (m_sdlRect.y > m_anchorPosY) throw std::runtime_error("Rect - values out of range");
}
TEST_CASE("Rect"){
	Rect r(0, 0, 100, 100, Rect::AnchorMode::LEFT, Rect::AnchorMode::TOP);

	SUBCASE("Rect testing Positions and edges") {
		CHECK(r.getPosX() == 0);
		CHECK(r.getPosY() == 0);
		CHECK(r.getWidth() == 100);
		CHECK(r.getHeight() == 100);
		CHECK(r.getLeft() == 0);
		CHECK(r.getTop() == 0);
		CHECK(r.getRight() == 100);
		CHECK(r.getBottom() == 100);
		CHECK(r.containsPoint(0, 0));
		CHECK(r.containsPoint(50, 50));
		CHECK(r.containsPoint(100, 100));
		CHECK(!r.containsPoint(101, 101));
		CHECK(!r.containsPoint(-1, -1));
		CHECK(!r.containsPoint(101, 0));
		CHECK(!r.containsPoint(0, 101));
		r.setPos(50, 50);
		CHECK(r.getPosX() == 50);
		CHECK(r.getPosY() == 50);
		r.setPosX(100);
		CHECK(r.getPosX() == 100);
		CHECK(r.getPosY() == 50);
		r.setPosY(100);
		CHECK(r.getPosX() == 100);
		CHECK(r.getPosY() == 100);

	}
	SUBCASE("Rect testing Dimensions") {
		r.setDimensions(200, 200);
		CHECK(r.getWidth() == 200);
		CHECK(r.getHeight() == 200);
		CHECK(r.getLeft() == 0);
		CHECK(r.getTop() == 0);
		CHECK(r.getRight() == 200);
		CHECK(r.getBottom() == 200);
		r.setWidth(300);
		CHECK(r.getWidth() == 300);
		CHECK(r.getHeight() == 200);
		r.setHeight(300);
		CHECK(r.getWidth() == 300);
		CHECK(r.getHeight() == 300);
		CHECK_THROWS(r.setWidth(-100));
		CHECK_THROWS(r.setHeight(-100));
	}
	SUBCASE("Rect testing Dimensions with keep aspect") {
		r.setWidthKeepAspect(200);
		CHECK(r.getWidth() == 200);
		CHECK(r.getHeight() == 200);
		r.setHeightKeepAspect(200);
		CHECK(r.getWidth() == 200);
		CHECK(r.getHeight() == 200);

		r.setDimensions(100,0);
		r.setWidthKeepAspect(200);
		CHECK(r.getWidth() == 200);
		CHECK(r.getHeight() == 0);

		r.setWidthKeepAspect(100, 2);
		CHECK(r.getWidth() == 100);
		CHECK(r.getHeight() == 50);
		r.setHeightKeepAspect(100, 2);
		CHECK(r.getWidth() == 200);
		CHECK(r.getHeight() == 100);
		r.setWidthKeepAspect(100, 0.5);
		CHECK(r.getWidth() == 100);
		CHECK(r.getHeight() == 200);
		r.setHeightKeepAspect(100, 0.5);
		CHECK(r.getWidth() == 50);
		CHECK(r.getHeight() == 100);
		CHECK_THROWS(r.setWidthKeepAspect(100, -1));
		CHECK_THROWS(r.setWidthKeepAspect(100, 0));
		CHECK_THROWS(r.setWidthKeepAspect(-100, 1));
		CHECK_THROWS(r.setHeightKeepAspect(100, -1));
		CHECK_THROWS(r.setHeightKeepAspect(-100, 1));
	}
	SUBCASE("Rect testing AnchorMode") {
		r.setAnchorModeX(Rect::AnchorMode::RIGHT);
		CHECK(r.getLeft() == -100);
		CHECK(r.getRight() == 0);
		CHECK(r.getTop() == 0);
		r.setAnchorModeY(Rect::AnchorMode::BOTTOM);
		CHECK(r.getTop() == -100);
		CHECK(r.getBottom() == 0);
		CHECK_THROWS(r.setAnchorModeX(Rect::AnchorMode::BOTTOM));
		CHECK_THROWS(r.setAnchorModeY(Rect::AnchorMode::LEFT));
	}
}
