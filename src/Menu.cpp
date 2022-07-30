#include "Menu.h"

Menu::Menu(const std::shared_ptr<Window> window, const std::shared_ptr<const Font>& font)
	: Event(window)
	, m_title("res/sprites/MainMenu_Title.png", window)
	, m_playButton(font, "play", window, 0xFF)
	, m_vsText(font, "vs.", window, 0xFF)
	, m_player1Text(font, m_actorNames[m_player1Selection], window, 0xFF)
	, m_player2Text(font, m_actorNames[m_player2Selection], window, 0xFF)
{
	m_title      .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_playButton .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_vsText     .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_player1Text.rect.setAnchorModeX(Rect::AnchorMode::RIGHT ).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_player2Text.rect.setAnchorModeX(Rect::AnchorMode::LEFT  ).setAnchorModeY(Rect::AnchorMode::CENTER);

	onWindowResized(window->getWidth(), window->getHeight());
}

void Menu::draw() {
	m_title.draw();
	m_playButton.draw();
	m_vsText.draw();
	m_player1Text.draw();
	m_player2Text.draw();
}

void Menu::adjustSizePlayer1(int width, int height) {
	float aspect = (float)m_player1Text.texture->getWidth()/m_player1Text.texture->getHeight();
	m_player1Text.rect.setHeightKeepAspect(height/10, aspect).setPos(width/2-height/8, height/2);
}

void Menu::adjustSizePlayer2(int width, int height) {
	float aspect = (float)m_player2Text.texture->getWidth()/m_player2Text.texture->getHeight();
	m_player2Text.rect.setHeightKeepAspect(height/10, aspect).setPos(width/2+height/8, height/2);
}

void Menu::onWindowResized(int width, int height) {
	float aspect = (float)m_title.texture->getWidth()/m_title.texture->getHeight();
	m_title.rect.setHeightKeepAspect(height/8, aspect).setPos(width/2, height/5);

	aspect = (float)m_playButton.texture->getWidth()/m_playButton.texture->getHeight();
	m_playButton.rect.setHeightKeepAspect(height/8, aspect).setPos(width/2, 13*height/20);

	aspect = (float)m_vsText.texture->getWidth()/m_vsText.texture->getHeight();
	m_vsText.rect.setHeightKeepAspect(height/20, aspect).setPos(width/2, height/2);

	adjustSizePlayer1(width, height);
	adjustSizePlayer2(width, height);
}

void Menu::onLeftClick(int32_t x, int32_t y) {
	if (m_player1Text.rect.containsPoint(x, y)) {
		m_player1Selection++;
		m_player1Selection %= sizeof(m_actorNames)/sizeof(*m_actorNames);
		m_player1Text.text = m_actorNames[m_player1Selection];
		m_player1Text.update(m_window);
		adjustSizePlayer1(m_window->getWidth(), m_window->getHeight());
	}
	if (m_player2Text.rect.containsPoint(x, y)) {
		m_player2Selection++;
		m_player2Selection %= sizeof(m_actorNames)/sizeof(*m_actorNames);
		m_player2Text.text = m_actorNames[m_player2Selection];
		m_player2Text.update(m_window);
		adjustSizePlayer2(m_window->getWidth(), m_window->getHeight());
	}
}
