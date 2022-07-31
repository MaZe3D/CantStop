#include "GameRoundDrawer.h"
#include "util/log.h"

GameRoundDrawer::GameRoundDrawer(const std::shared_ptr<Window> window, const std::shared_ptr<const Font>& font)
	: Event(window)
	, m_background("res/sprites/Game_Background.png", window)
	, m_textureBarPlayer1(window->loadTexture("res/sprites/Game_Player1_Bar.png"))
	, m_textureBarPlayer2(window->loadTexture("res/sprites/Game_Player2_Bar.png"))
	, m_textureBarTemp(window->loadTexture("res/sprites/Game_Temp_Bar.png"))

{
	m_background.rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);

	for (int i = 0; i < 11; i++) {
		m_bars.push_back(Bars(TextureDrawable(m_textureBarPlayer1), TextureDrawable(m_textureBarPlayer2), TextureDrawable(m_textureBarTemp)));
	}

	for (auto& bars : m_bars) {
		bars.barPlayer1.rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::BOTTOM);
		bars.barPlayer2.rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::BOTTOM);
		bars.barTemp   .rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::BOTTOM);
	}

	for (int i = 0; i < 6; i++) {
		m_diceTextures.push_back(window->loadTexture("res/sprites/Dice_Player1_" + std::to_string(i + 1) + ".png"));
	}
	for (int i = 0; i < 6; i++) {
		m_diceTextures.push_back(window->loadTexture("res/sprites/Dice_Player2_" + std::to_string(i + 1) + ".png"));
	}

	for (int i = 0; i < 4; i++) {
		m_diceTextureDrawable.push_back(TextureDrawable(m_diceTextures[i]));
	}

	onWindowResized(window->getWidth(), window->getHeight());
}

void GameRoundDrawer::setGameRound(const std::shared_ptr<GameRound>& round) {
	m_round = round;
}

void GameRoundDrawer::draw() {
	m_background.draw();
	setBars();

	for(auto &bars : m_bars) {
		bars.draw();
	}

	setDiceTextures();
	for (int i = 0; i < 4; i++) {
		m_diceTextureDrawable[i].draw();
	}
}

void GameRoundDrawer::setBars() {
	for (unsigned int i = 0; i < m_bars.size(); i++) {
		m_bars[i].barPlayer1.rect.setHeight(m_round->getBoard().getColumn(i).actor1Marker * m_barIncrement);
		m_bars[i].barPlayer2.rect.setHeight(m_round->getBoard().getColumn(i).actor2Marker * m_barIncrement);
		switch (m_round->getCurrentActor()) {
		case ActorEnum::ACTOR1:
			m_bars[i].barTemp.rect
				.setPos(m_bars[i].barPlayer1.rect.getPosX(), m_bars[i].barPlayer1.rect.getPosY() - m_bars[i].barPlayer1.rect.getHeight())
				.setHeight(m_round->getBoard().getColumn(i).runnerOffset * m_barIncrement);
			break;
		case ActorEnum::ACTOR2:
			m_bars[i].barTemp.rect
				.setPos(m_bars[i].barPlayer2.rect.getPosX(), m_bars[i].barPlayer2.rect.getPosY() - m_bars[i].barPlayer2.rect.getHeight())
				.setHeight(m_round->getBoard().getColumn(i).runnerOffset * m_barIncrement);
			break;
		default:
			break;
		}
	}
}

void GameRoundDrawer::onWindowResized(int width, int height) {
	m_background.rect.setHeightKeepAspect(height, m_background.getTexture()->getAspect()).setPos(width/2, height/2);

	const double firstBarPosX = (width/2) - (height * (786.5/2160));
	const double firstBarPosY = height * (1657./2160.);
	const double barWidth = height * (1./20.);
	const double barDistance = height * (152.6/2160.);
	const double barPairDistance = height * (47./2160.);
	m_barIncrement = height * (7./135.);

	for (unsigned int i = 0; i < m_bars.size(); i++) {
		m_bars[i].barPlayer1.rect
			.setPos(firstBarPosX + (i * barDistance), firstBarPosY)
			.setWidth(barWidth);
		m_bars[i].barPlayer2.rect
			.setPos(firstBarPosX + barPairDistance + (i * barDistance), firstBarPosY)
			.setWidth(barWidth);
		m_bars[i].barTemp.rect
			.setPos(firstBarPosX + barPairDistance + (i * barDistance), firstBarPosY)
			.setWidth(barWidth);
	}

	const double diceWidth(height * (150./2160.));
	const double diceSpaceWidth(diceWidth * (1./10.));

	for (int i = 0; i < 4; i++) {
		m_diceTextureDrawable[i].rect
			.setWidth(diceWidth)
			.setHeight(diceWidth);
	}

	m_diceTextureDrawable[0].rect.setPos(firstBarPosX - (400./2160.)*height, firstBarPosY - (13*m_barIncrement));
	m_diceTextureDrawable[1].rect.setPos(m_diceTextureDrawable[0].rect.getPosX() + diceWidth + diceSpaceWidth, m_diceTextureDrawable[0].rect.getPosY());
	m_diceTextureDrawable[2].rect.setPos(m_diceTextureDrawable[0].rect.getPosX(), m_diceTextureDrawable[0].rect.getPosY() + diceWidth + diceSpaceWidth);
	m_diceTextureDrawable[3].rect.setPos(m_diceTextureDrawable[2].rect.getPosX() + diceWidth + diceSpaceWidth, m_diceTextureDrawable[2].rect.getPosY());
}

void GameRoundDrawer::onLeftClick(int32_t x, int32_t y) {
	if (!m_round) return;
	if (!m_round->isOver()) m_round->nextStep();
	const DiceThrow& diceThrow = m_round->getDiceThrow();
	DEBUG_LOG_NO_NL("combinationCount: " << (int)diceThrow.getCombinationCount() << std::endl);
	for (int i = 0; i < diceThrow.getCombinationCount(); i++) {
		DEBUG_LOG_NO_NL("combination #" << i << ": " << (int)diceThrow.getCombination(i).a << " " << (int)diceThrow.getCombination(i).b << std::endl);
	}
	DEBUG_LOG_NO_NL("\ncurrent player: " << ((m_round->getCurrentActor() == ActorEnum::ACTOR1) ? "ACTOR 1" : "ACTOR 2"));
	DEBUG_LOG_NO_NL("\nnext step: " << ((m_round->getNextStep() == GameRound::NextStep::CHOOSE_DICE_COMBINATION) ? "CHOOSE_DICE_COMBINATION" : "CHOOSE_TO_CONTINUE_OR_STOP"));
	DEBUG_LOG_NO_NL("\nactor1Marker:");
	for (unsigned int i = 0; i < m_bars.size(); i++)
		DEBUG_LOG_NO_NL(" " << (int)m_round->getBoard().getColumn(i).actor1Marker);
	DEBUG_LOG_NO_NL("\nactor2Marker:");
	for (unsigned int i = 0; i < m_bars.size(); i++)
		DEBUG_LOG_NO_NL(" " << (int)m_round->getBoard().getColumn(i).actor2Marker);
	DEBUG_LOG_NO_NL("\nrunnerOffset:");
	for (unsigned int i = 0; i < m_bars.size(); i++)
		DEBUG_LOG_NO_NL(" " << (int)m_round->getBoard().getColumn(i).runnerOffset);
	DEBUG_LOG_NO_NL("\n-----------------------------------------------------------------------------------------\n");
}

void GameRoundDrawer::setDiceTextures()
{
	int offset = 0;
	if (m_round->getCurrentActor() == ActorEnum::ACTOR2) offset = 6;
	
	for (int i = 0; i < 4; i++) {
		m_diceTextureDrawable[i].setTexture(m_diceTextures[i+offset]);
	}
}

GameRoundDrawer::Bars::Bars(TextureDrawable barPlayer1, TextureDrawable barPlayer2, TextureDrawable barTemp)
	: barPlayer1(barPlayer1)
	, barPlayer2(barPlayer2)
	, barTemp(barTemp) {
}

void GameRoundDrawer::Bars::draw() {
	barPlayer1.draw();
	barPlayer2.draw();
	barTemp.draw();
}
