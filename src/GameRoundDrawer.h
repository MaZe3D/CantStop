#pragma once
#include "mysdl/Events.h"
#include "mysdl/Window.h"
#include "mysdl/Font.h"
#include "drawables/TextureDrawable.h"
#include "drawables/TextDrawable.h"
#include "logic/GameRound.h"

class GameRoundDrawer : WindowResizedEvent, LeftClickEvent {
public:
	GameRoundDrawer(const std::shared_ptr<Window> window, const std::shared_ptr<const Font>& font);

	void draw(std::shared_ptr<GameRound>& round);

private:
	TextureDrawable m_background;

	void onWindowResized(int width, int height) override;
	void onLeftClick(int32_t x, int32_t y) override;
};
