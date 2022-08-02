#include "Menu.h"
#include "Game.h"
#include "logic/actors/Player.h"
#include "logic/actors/bots/SmartBot.h"
#include "logic/actors/bots/GreedyBot.h"
#include "logic/actors/bots/RandomBot.h"

Menu::Menu(const std::shared_ptr<Window> window, Game& game, const std::shared_ptr<const Font>& font1, const std::shared_ptr<const Font>& font2)
	: Event(window)
	, m_game(game)
	, m_background("res/sprites/MainMenu_Background.png", window)
	, m_title("res/sprites/MainMenu_Title.png", window)
	, m_playButton("res/sprites/MainMenu_StartGame_Button.png", window)
	, m_vs("res/sprites/MainMenu_PlayerSelect_Background.png", window)
	, m_player1Text(font2, m_actorNames[m_player1Selection], window, 0xFFFFFFFF)
	, m_player2Text(font2, m_actorNames[m_player2Selection], window, 0xFFFFFFFF)
	, m_continueButton(font1, " continue", window, 0xFFFFFFFF)
{
	m_background .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_title      .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_playButton .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_vs     .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_player1Text.rect.setAnchorModeX(Rect::AnchorMode::RIGHT ).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_player2Text.rect.setAnchorModeX(Rect::AnchorMode::LEFT  ).setAnchorModeY(Rect::AnchorMode::CENTER);

	onWindowResized(window->getWidth(), window->getHeight());
}

void Menu::activate() {
	DrawEvent::subscribe();
	WindowResizedEvent::subscribe();
	LeftClickEvent::subscribe();
}

void Menu::deactivate() {
	DrawEvent::unsubscribe();
	WindowResizedEvent::unsubscribe();
	LeftClickEvent::unsubscribe();
}

void Menu::onDraw() {
	m_background.draw();
	m_title.draw();
	m_playButton.draw();
	m_vs.draw();
	m_player1Text.draw();
	m_player2Text.draw();
	if (m_round && !m_round->isOver())
		m_continueButton.draw();
}

void Menu::restart() {
	activate();
	onWindowResized(m_window->getWidth(), m_window->getHeight());
}

void Menu::adjustSizePlayer1(int width, int height) {
	m_player1Text.rect.setHeightKeepAspect(height/10, m_player1Text.getTexture()->getAspect()).setPos(width/2-height/8, height/2);
}

void Menu::adjustSizePlayer2(int width, int height) {
	m_player2Text.rect.setHeightKeepAspect(height/10, m_player2Text.getTexture()->getAspect()).setPos(width/2+height/8, height/2);
}

void Menu::onWindowResized(int width, int height) {
	m_background.rect.setHeightKeepAspect(height   , m_background.getTexture()->getAspect()).setPos(width/2, height/2);
	m_title     .rect.setHeightKeepAspect(height/8 , m_title     .getTexture()->getAspect()).setPos(width/2, height/5);
	m_playButton.rect.setHeightKeepAspect(height/11, m_playButton.getTexture()->getAspect()).setPos(width/2, 13*height/20);
	m_vs        .rect.setHeightKeepAspect(height/7 , m_vs        .getTexture()->getAspect()).setPos(width/2, 0.49*height);

	adjustSizePlayer1(width, height);
	adjustSizePlayer2(width, height);

	m_continueButton.rect.setHeightKeepAspect(height/20, m_continueButton.getTexture()->getAspect());
	m_continueButton.rect.setPosX(width/2-height*16/9/2);
}

void Menu::onLeftClick(int32_t x, int32_t y) {
	if (m_player1Text.rect.containsPoint(x, y)) {
		m_player1Selection++;
		m_player1Selection %= sizeof(m_actorNames)/sizeof(*m_actorNames);
		m_player1Text.text = m_actorNames[m_player1Selection];
		m_player1Text.update(m_window);
		adjustSizePlayer1(m_window->getWidth(), m_window->getHeight());
	}
	else if (m_player2Text.rect.containsPoint(x, y)) {
		m_player2Selection++;
		m_player2Selection %= sizeof(m_actorNames)/sizeof(*m_actorNames);
		m_player2Text.text = m_actorNames[m_player2Selection];
		m_player2Text.update(m_window);
		adjustSizePlayer2(m_window->getWidth(), m_window->getHeight());
	}
	else if (m_playButton.rect.containsPoint(x, y)) {
		std::shared_ptr<Actor> actor1;
		switch(m_player1Selection) {
			case 0: actor1 = std::make_shared<Player>(); break;
			case 1: actor1 = std::make_shared<SmartBot>(); break;
			case 2: actor1 = std::make_shared<GreedyBot>(); break;
			case 3: actor1 = std::make_shared<RandomBot>(); break;
		}
		std::shared_ptr<Actor> actor2;
		switch(m_player2Selection) {
			case 0: actor2 = std::make_shared<Player>(); break;
			case 1: actor2 = std::make_shared<SmartBot>(); break;
			case 2: actor2 = std::make_shared<GreedyBot>(); break;
			case 3: actor2 = std::make_shared<RandomBot>(); break;
		}
		m_round = std::make_shared<GameRound>(actor1, actor2, MersenneTwister());
		deactivate();
		m_game.startNewRound(m_round);
	}
	else if (m_round && !m_round->isOver() && m_continueButton.rect.containsPoint(x, y)) {
		deactivate();
		m_game.startNewRound(m_round);
	}

}
