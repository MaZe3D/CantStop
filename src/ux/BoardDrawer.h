#pragma once
#include "mysdl/Events.h"
#include "logic/GameRound.h"
#include "drawables/TextureDrawable.h"

class BoardDrawer : DrawEvent, WindowResizedEvent {
public:
	BoardDrawer(const std::shared_ptr<Window> window);

	void setGameRound(const std::shared_ptr<GameRound>& round);

	void update();

	void activate();
	void deactivate();

	struct Bars
	{
		TextureDrawable barPlayer1;
		TextureDrawable barPlayer2;
		TextureDrawable barTemp;

		Bars(TextureDrawable barPlayer1, TextureDrawable barPlayer2, TextureDrawable barTemp);

		void draw();
	};

	double m_barIncrement;
	
	std::vector<Bars> m_bars;

	void setBars();

private:
	std::shared_ptr<GameRound> m_round;

	const std::shared_ptr<const Texture> m_textureBarPlayer1;
	const std::shared_ptr<const Texture> m_textureBarPlayer2;
	const std::shared_ptr<const Texture> m_textureBarTemp;

	void onDraw() override;
	void onWindowResized(int width, int height) override;

};
