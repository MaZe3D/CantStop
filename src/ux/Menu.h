#pragma once
#include "mysdl/Events.h"
#include "mysdl/Window.h"
#include "drawables/TextureDrawable.h"
#include "drawables/TextDrawable.h"
#include "logic/GameRound.h"

class GameRoundDrawer;

class Menu : DrawEvent, WindowResizedEvent, LeftClickEvent {
public:
	Menu(const std::shared_ptr<Window> window, GameRoundDrawer& gameDrawer, const std::shared_ptr<const Font>& font1, const std::shared_ptr<const Font>& font2);

	void activate();
	void deactivate();

private:
	uint8_t m_actor1SelectionID = 0;
	uint8_t m_actor2SelectionID = 1;

	GameRoundDrawer& m_gameDrawer;
	std::shared_ptr<GameRound> m_round;

	TextureDrawable m_background;
	TextureDrawable m_title;
	TextureDrawable m_playButton;
	TextureDrawable m_vs;
	TextDrawable m_player1Text;
	TextDrawable m_player2Text;
	TextDrawable m_continueButton;

	void onDraw() override;
	void onWindowResized(int width, int height) override;
	void onLeftClick(int32_t x, int32_t y) override;

	std::shared_ptr<Actor> createActorFromSelectionID(uint8_t id) const;

};
