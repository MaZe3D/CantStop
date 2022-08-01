#pragma once
#include "mysdl/Events.h"
#include "mysdl/Window.h"
#include "drawables/TextureDrawable.h"
#include "drawables/TextDrawable.h"

class Game;

class Menu : WindowResizedEvent, LeftClickEvent {
public:
	Menu(const std::shared_ptr<Window> window, Game& game, const std::shared_ptr<const Font>& font);

	void draw();
	void restart();

private:
	const char* m_actorNames[4] { "HUMAN", "SMART BOT", "GREEDY BOT", "RANDOM BOT" };

	uint8_t m_player1Selection = 0;
	uint8_t m_player2Selection = 1;

	Game& m_game;

	TextureDrawable m_background;
	TextureDrawable m_title;
	TextureDrawable m_playButton;
	TextureDrawable m_vs;
	TextDrawable m_player1Text;
	TextDrawable m_player2Text;

	void adjustSizePlayer1(int width, int height);
	void adjustSizePlayer2(int width, int height);

	void onWindowResized(int width, int height) override;
	void onLeftClick(int32_t x, int32_t y) override;

};
