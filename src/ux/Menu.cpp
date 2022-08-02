#include "Menu.h"
#include "ux/GameRoundDrawer.h"
#include "logic/actors/Player.h"
#include "logic/actors/bots/SmartBot.h"
#include "logic/actors/bots/GreedyBot.h"
#include "logic/actors/bots/SafeBot.h"
#include "logic/actors/bots/RandomBot.h"

namespace {
	const uint8_t ACTOR_NAME_COUNT = 5;
	const char* ACTOR_NAMES[ACTOR_NAME_COUNT] = { "HUMAN", "SMART BOT", "GREEDY BOT", "SAFE BOT", "RANDOM BOT" };
}

Menu::Menu(const std::shared_ptr<Window> window, GameRoundDrawer& gameDrawer, const std::shared_ptr<const Font>& font1, const std::shared_ptr<const Font>& font2)
	: Event(window)
	, m_gameDrawer(gameDrawer)
	, m_background("res/sprites/MainMenu_Background.png", window)
	, m_title("res/sprites/MainMenu_Title.png", window)
	, m_playButton("res/sprites/MainMenu_StartGame_Button.png", window)
	, m_vs("res/sprites/MainMenu_PlayerSelect_Background.png", window)
	, m_actor1Text(font2, ACTOR_NAMES[m_actor1SelectionID], window, 0xFFFFFFFF)
	, m_actor2Text(font2, ACTOR_NAMES[m_actor2SelectionID], window, 0xFFFFFFFF)
	, m_continueButton(font1, " continue", window, 0xFFFFFFFF)
{
	m_background    .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_title         .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_playButton    .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_vs            .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_actor1Text    .rect.setAnchorModeX(Rect::AnchorMode::RIGHT ).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_actor2Text    .rect.setAnchorModeX(Rect::AnchorMode::LEFT  ).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_continueButton.rect.setAnchorModeX(Rect::AnchorMode::LEFT  ).setAnchorModeY(Rect::AnchorMode::TOP  );
}

void Menu::activate() {
	DrawEvent         ::subscribe();
	WindowResizedEvent::subscribe();
	LeftClickEvent    ::subscribe();
	onWindowResized(m_window->getWidth(), m_window->getHeight());
}

void Menu::deactivate() {
	DrawEvent         ::unsubscribe();
	WindowResizedEvent::unsubscribe();
	LeftClickEvent    ::unsubscribe();
}

void Menu::onWindowResized(int width, int height) {
	m_background    .setHeightKeepAspect(height   ).rect.setPos(width/2           , height/2    );
	m_title         .setHeightKeepAspect(height/8 ).rect.setPos(width/2           , height/5    );
	m_playButton    .setHeightKeepAspect(height/11).rect.setPos(width/2           , height*13/20);
	m_vs            .setHeightKeepAspect(height/7 ).rect.setPos(width/2           , height*0.49 );
	m_actor1Text    .setHeightKeepAspect(height/10).rect.setPos(width/2-height/8  , height/2    );
	m_actor2Text    .setHeightKeepAspect(height/10).rect.setPos(width/2+height/8  , height/2    );
	m_continueButton.setHeightKeepAspect(height/20).rect.setPos(width/2-height*8/9, 0           );
}

void Menu::onLeftClick(int32_t x, int32_t y) {
	if (m_actor1Text.rect.containsPoint(x, y)) {
		m_actor1SelectionID = (m_actor1SelectionID+1) % ACTOR_NAME_COUNT;
		m_actor1Text.text = ACTOR_NAMES[m_actor1SelectionID];
		m_actor1Text.update(m_window, true);
		m_actor1Text.setHeightKeepAspect(m_actor1Text.rect.getHeight());
	}
	else if (m_actor2Text.rect.containsPoint(x, y)) {
		m_actor2SelectionID = (m_actor2SelectionID+1) % ACTOR_NAME_COUNT;
		m_actor2Text.text = ACTOR_NAMES[m_actor2SelectionID];
		m_actor2Text.update(m_window, true);
		m_actor2Text.setHeightKeepAspect(m_actor2Text.rect.getHeight());
	}
	else if (m_playButton.rect.containsPoint(x, y)) {
		auto actor1 = createActorFromSelectionID(m_actor1SelectionID);
		auto actor2 = createActorFromSelectionID(m_actor2SelectionID);
		m_round = std::make_shared<GameRound>(actor1, actor2, MersenneTwister());
		m_gameDrawer.setGameRound(m_round);
		deactivate();
	}
	else if (m_round && !m_round->isOver() && m_continueButton.rect.containsPoint(x, y)) {
		deactivate();
		m_gameDrawer.setGameRound(m_round);
	}
}

void Menu::onDraw() {
	m_background .draw();
	m_title      .draw();
	m_playButton .draw();
	m_vs         .draw();
	m_actor1Text .draw();
	m_actor2Text .draw();
	if (m_round && !m_round->isOver())
		m_continueButton.draw();
}

std::shared_ptr<Actor> Menu::createActorFromSelectionID(uint8_t id) const {
	switch(id) {
		case 4: return std::make_shared<RandomBot>(); break;
		case 3: return std::make_shared<SafeBot>();   break;
		case 2: return std::make_shared<GreedyBot>(); break;
		case 1: return std::make_shared<SmartBot>();  break;
		default: return std::make_shared<Player>();   break;
	}
}
