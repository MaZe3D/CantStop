#include "GameRound.h"

GameRound::GameRound(const std::shared_ptr<Window> window, const std::shared_ptr<const Font>& font)
	: Event(window)
	, m_background("res/sprites/Game_Background.png", window)
{
	m_background .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	onWindowResized(window->getWidth(), window->getHeight());
}

void GameRound::draw() {
	m_background.draw();
}

void GameRound::onWindowResized(int width, int height) {
	m_background.rect.setHeightKeepAspect(height, m_background.getTexture()->getAspect()).setPos(width/2, height/2);
}

void GameRound::onLeftClick(int32_t x, int32_t y) {
}
