#pragma once
#include "mysdl/Events.h"
#include "mysdl/Window.h"
#include "drawables/TextureDrawable.h"
#include "drawables/TextDrawable.h"

class Menu : WindowResizedEvent, LeftClickEvent {
public:
	Menu(const std::shared_ptr<Window> window, const std::shared_ptr<const Font>& font);

	void draw();

private:
	const char* m_actorNames[4] { "Human", "Random Bot", "Greedy Bot", "Smart Bot" };

	uint8_t m_player1Selection = 0;
	uint8_t m_player2Selection = 1;

	TextureDrawable m_title;
	TextDrawable m_playButton;
	TextDrawable m_vsText;
	TextDrawable m_player1Text;
	TextDrawable m_player2Text;

	void adjustSizePlayer1(int width, int height);
	void adjustSizePlayer2(int width, int height);

	void onWindowResized(int width, int height) override;
	void onLeftClick(int32_t x, int32_t y) override;

};
