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

	void setGameRound(const std::shared_ptr<GameRound>& round);
	void draw();

private:

	std::shared_ptr<GameRound> m_round;

	struct Bars
	{
		TextureDrawable barPlayer1;
		TextureDrawable barPlayer2;
		TextureDrawable barTemp;

		Bars(TextureDrawable barPlayer1, TextureDrawable barPlayer2, TextureDrawable barTemp);

		void draw();
	};

	TextureDrawable m_background;

	int m_barIncrement;
	
	const std::shared_ptr<const Texture> m_textureBarPlayer1;
	const std::shared_ptr<const Texture> m_textureBarPlayer2;
	const std::shared_ptr<const Texture> m_textureBarTemp;

	std::vector<Bars> m_bars;

	void setBars();

	void onWindowResized(int width, int height) override;
	void onLeftClick(int32_t x, int32_t y) override;
};
