#pragma once
#include "mysdl/Events.h"
#include "mysdl/Window.h"
#include "drawables/TextureDrawable.h"
#include "drawables/TextDrawable.h"
#include "logic/GameRound.h"

class Game;

class Menu : DrawEvent, WindowResizedEvent, LeftClickEvent {
public:
	Menu(const std::shared_ptr<Window> window, Game& game, const std::shared_ptr<const Font>& font1, const std::shared_ptr<const Font>& font2);

	void activate();
	void deactivate();

	void restart();

private:
	const char* m_actorNames[4] { "HUMAN", "SMART BOT", "GREEDY BOT", "RANDOM BOT" };

	uint8_t m_player1Selection = 0;
	uint8_t m_player2Selection = 1;

	Game& m_game;
	std::shared_ptr<GameRound> m_round;

	TextureDrawable m_background;
	TextureDrawable m_title;
	TextureDrawable m_playButton;
	TextureDrawable m_vs;
	TextDrawable m_player1Text;
	TextDrawable m_player2Text;
	TextDrawable m_continueButton;

	void adjustSizePlayer1(int width, int height);
	void adjustSizePlayer2(int width, int height);

	void onDraw() override;
	void onWindowResized(int width, int height) override;
	void onLeftClick(int32_t x, int32_t y) override;

};
