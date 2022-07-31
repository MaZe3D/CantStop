#pragma once
#include "mysdl/Events.h"
#include "mysdl/Window.h"
#include "drawables/TextureDrawable.h"
#include "drawables/TextDrawable.h"

class Menu : WindowResizedEvent, LeftClickEvent {
public:
	Menu(const std::shared_ptr<Window> window, const std::shared_ptr<const Font>& font1, const std::shared_ptr<const Font>& font2);

	void draw();

private:
	//const char* m_actorNames[4] { "Human", "Random Bot", "Greedy Bot", "Smart Bot" };
	const char* m_actorNames[4] { "HUMAN", "RANDOM BOT", "GREEDY BOT", "SMART BOT" };

	uint8_t m_player1Selection = 0;
	uint8_t m_player2Selection = 1;

	TextureDrawable m_background;
	TextureDrawable m_title;
	TextDrawable m_playButton;
	TextureDrawable m_vs;
	TextDrawable m_player1Text;
	TextDrawable m_player2Text;

	void adjustSizePlayer1(int width, int height);
	void adjustSizePlayer2(int width, int height);

	void onWindowResized(int width, int height) override;
	void onLeftClick(int32_t x, int32_t y) override;

};
