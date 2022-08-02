#pragma once
#include "mysdl/Events.h"
#include "mysdl/Window.h"
#include "mysdl/Font.h"
#include "drawables/TextureDrawable.h"
#include "drawables/TextDrawable.h"
#include "logic/GameRound.h"

class Menu;

class GameRoundDrawer : DrawEvent, WindowResizedEvent, LeftClickEvent {
public:
	GameRoundDrawer(const std::shared_ptr<Window> window, Menu& menu, const std::shared_ptr<const Font>& font);

	void activate();
	void deactivate();

	void setGameRound(const std::shared_ptr<GameRound>& round);

private:

	Menu& m_menu;

	std::shared_ptr<GameRound> m_round;

	TextureDrawable m_background;
	TextDrawable m_menuButtonText;
	const std::shared_ptr<const Texture> m_textureBarPlayer1;
	const std::shared_ptr<const Texture> m_textureBarPlayer2;
	const std::shared_ptr<const Texture> m_textureBarTemp;


	std::shared_ptr<const Texture> m_victoryTextures[2];
	std::shared_ptr<TextureDrawable> m_victoryDrawable;
	TextDrawable m_victoryText;

	TextureDrawable m_btnCombinationSelectFrame[2];
	std::shared_ptr<const Texture> m_btnCombinationSelectTexture[2];
	std::shared_ptr<TextDrawable> m_btnCombinationSelectText[6];
	std::vector<std::shared_ptr<TextureDrawable>> m_btnCombinationSelectDrawable;

	std::shared_ptr<TextDrawable> m_stopText;
	std::shared_ptr<TextDrawable> m_continueText;

	void updateCombinationButtons();
	void drawCombinationButtons();

	struct Bars
	{
		TextureDrawable barPlayer1;
		TextureDrawable barPlayer2;
		TextureDrawable barTemp;

		Bars(TextureDrawable barPlayer1, TextureDrawable barPlayer2, TextureDrawable barTemp);

		void draw();
	};

	std::vector<std::shared_ptr<const Texture>> m_diceTextures; // 0-5 Player 1, 6-11 Player 2

	std::vector<TextureDrawable> m_diceTextureDrawable;

	void setDiceTextures();


	double m_barIncrement;
	
	std::vector<Bars> m_bars;

	void setBars();

	void onDraw() override;
	void onWindowResized(int width, int height) override;
	void onLeftClick(int32_t x, int32_t y) override;

	void drawVictoryScreen(ActorEnum winner);
};
