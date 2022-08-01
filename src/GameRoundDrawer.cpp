#include "GameRoundDrawer.h"
#include "util/log.h"

GameRoundDrawer::GameRoundDrawer(const std::shared_ptr<Window> window, const std::shared_ptr<const Font>& font)
	: Event(window)
	, m_background("res/sprites/Game_Background.png", window)
	, m_textureBarPlayer1(window->loadTexture("res/sprites/Game_Player1_Bar.png"))
	, m_textureBarPlayer2(window->loadTexture("res/sprites/Game_Player2_Bar.png"))
	, m_textureBarTemp(window->loadTexture("res/sprites/Game_Temp_Bar.png"))
	, m_victoryText(font, "Click to continue", window)
{
	WindowEvent::unsubscribe();
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
		m_diceTextureDrawable[i].rect.setAnchorModeX(Rect::AnchorMode::CENTER);
	}

	for (int i = 0; i < 2; i++) {
		m_btnCombinationSelectTexture[i] = (window->loadTexture("res/sprites/Game_Player" + std::to_string(i + 1) + "_Select.png"));
	}

	for (int i = 0; i < 6; i++) {
		m_btnCombinationSelectText[i] = std::make_shared<TextDrawable>(font, " ", window);
		m_btnCombinationSelectText[i]->rect
			.setAnchorModeX(Rect::AnchorMode::CENTER)
			.setAnchorModeY(Rect::AnchorMode::CENTER);
	}

	for (int i = 0; i < 6; i++) {
		m_btnCombinationSelectDrawable.push_back(std::make_shared<TextureDrawable>(m_btnCombinationSelectTexture[0]));
	}

	for (int i = 0; i < 2; i++) {
		m_victoryTextures[i] = (window->loadTexture("res/sprites/Victory_Player" + std::to_string(i + 1) + ".png"));
	}
	m_victoryDrawable = std::make_shared<TextureDrawable>(m_victoryTextures[0]);
	m_victoryDrawable->rect
		.setAnchorModeX(Rect::AnchorMode::CENTER)
		.setAnchorModeY(Rect::AnchorMode::CENTER);

	m_victoryText.rect
		.setAnchorModeX(Rect::AnchorMode::CENTER)
		.setAnchorModeY(Rect::AnchorMode::TOP);

	//onWindowResized(window->getWidth(), window->getHeight());
}

void GameRoundDrawer::setGameRound(const std::shared_ptr<GameRound>& round) {
	m_round = round;
	WindowEvent::subscribe();
	setBars();
	setDiceTextures();
	updateCombinationButtons();
}

void GameRoundDrawer::draw() {
	m_background.draw();

	for(auto &bars : m_bars) {
		bars.draw();
	}

	for (int i = 0; i < 4; i++) {
		m_diceTextureDrawable[i].draw();
	}

	drawCombinationButtons();

	if (m_round->isOver())
	{
		drawVictoryScreen(m_round->getCurrentActorEnum());
	}
}

void GameRoundDrawer::setBars() {
	for (unsigned int i = 0; i < m_bars.size(); i++) {
		m_bars[i].barPlayer1.rect.setHeight(m_round->getBoard().getColumn(i).actor1Marker * m_barIncrement);
		m_bars[i].barPlayer2.rect.setHeight(m_round->getBoard().getColumn(i).actor2Marker * m_barIncrement);
		switch (m_round->getCurrentActorEnum()) {
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

	if (m_round) {
		setBars();
	}
	const double diceWidth(height * (150./2160.));
	const double diceSpaceWidth(diceWidth * (1./10.));

	for (int i = 0; i < 4; i++) {
		m_diceTextureDrawable[i].rect
			.setWidth(diceWidth)
			.setHeight(diceWidth);
	}
	
	int8_t mirrorFactor = (m_round->getCurrentActorEnum() == ActorEnum::ACTOR1) ? -1 : 1;
	
	for (int i = 0; i < 4; i++) {
		m_diceTextureDrawable[i].rect
			.setPos((width/2.) + mirrorFactor * (1200./2160.) * height + i * mirrorFactor * (diceWidth + diceSpaceWidth), firstBarPosY - m_barIncrement*13);
	}

	const double btnCombinationHight = (125./2160.) * height;
	const double btnCombinationDistance = (1/10) * btnCombinationHight;

	for(int i = 0; i < 6; i++) {
		m_btnCombinationSelectDrawable[i]->rect
			.setPos(m_diceTextureDrawable[(m_round->getCurrentActorEnum() == ActorEnum::ACTOR1) ? 3 : 0].rect.getPosX(), m_diceTextureDrawable[0].rect.getPosY() + 1.5 * m_diceTextureDrawable[0].rect.getHeight() + i * (btnCombinationHight + btnCombinationDistance))
			.setWidthKeepAspect(std::abs(m_diceTextureDrawable[0].rect.getPosX() - m_diceTextureDrawable[3].rect.getPosX()), m_btnCombinationSelectDrawable[i]->getTexture()->getAspect());
		m_btnCombinationSelectText[i]->rect
			.setPos(m_btnCombinationSelectDrawable[i]->rect.getPosX() + (m_btnCombinationSelectDrawable[i]->rect.getWidth()/2)
				, m_btnCombinationSelectDrawable[i]->rect.getPosY() + (m_btnCombinationSelectDrawable[i]->rect.getHeight()/2))
			.setHeightKeepAspect(m_btnCombinationSelectDrawable[i]->rect.getHeight()/2, m_btnCombinationSelectText[i]->getTexture()->getAspect());
	}

	m_diceTextureDrawable[(m_round->getCurrentActorEnum() == ActorEnum::ACTOR1) ? 3 : 0].rect.getPosX();

	m_victoryDrawable->rect
		.setHeightKeepAspect(height, m_victoryDrawable->getTexture()->getAspect())
		.setPos(width / 2., height / 2);

	m_victoryText.rect.setHeightKeepAspect(height*(70./2160.), m_victoryText.getTexture()->getAspect())
		.setPos(width / 2., height * (2033./2160.));
}

void GameRoundDrawer::onLeftClick(int32_t x, int32_t y) {
	if (!m_round) return;
	if (!m_round->isOver()) m_round->nextStep();
	
	setBars();
	setDiceTextures();
	updateCombinationButtons();

	onWindowResized(m_window->getWidth(), m_window->getHeight());

	const DiceThrow& diceThrow = m_round->getDiceThrow();
	DEBUG_LOG_NO_NL("combinationCount: " << (int)diceThrow.getCombinationCount() << std::endl);
	for (int i = 0; i < diceThrow.getCombinationCount(); i++) {
		DEBUG_LOG_NO_NL("combination #" << i << ": " << (int)diceThrow.getCombination(i).a << " " << (int)diceThrow.getCombination(i).b << std::endl);
	}
	DEBUG_LOG_NO_NL("\ncurrent player: " << ((m_round->getCurrentActorEnum() == ActorEnum::ACTOR1) ? "ACTOR 1" : "ACTOR 2"));
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
	if (m_round->getCurrentActorEnum() == ActorEnum::ACTOR2) offset = 6;
	
	for (int i = 0; i < 4; i++) {
		m_diceTextureDrawable[i].setTexture(m_diceTextures[m_round->getDiceThrow().getDie(i) -1 + offset]);
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

void GameRoundDrawer::drawVictoryScreen(ActorEnum winner) {
	switch (winner) {
	case ActorEnum::ACTOR1:
		m_victoryDrawable->setTexture(m_victoryTextures[0]);
		break;
	case ActorEnum::ACTOR2:
		m_victoryDrawable->setTexture(m_victoryTextures[1]);
		break;
	default:
		break;
	}

	m_victoryDrawable->draw();
	m_victoryText.draw();

}

void GameRoundDrawer::updateCombinationButtons() {
	for (int i = 0; i < m_round->getDiceThrow().getCombinationCount(); i++)
	{
		m_btnCombinationSelectText[i]->text = std::to_string(m_round->getDiceThrow().getCombination(i).a) 
			+ ((m_round->getDiceThrow().getCombination(i).b > 0) ? 
				" + " + std::to_string(m_round->getDiceThrow().getCombination(i).b) 
				: "");
		m_btnCombinationSelectText[i]->update(m_window);
		
		switch (m_round->getCurrentActorEnum()) {
		case ActorEnum::ACTOR1:
			m_btnCombinationSelectDrawable[i]->setTexture(m_btnCombinationSelectTexture[0]);
			break;
		case ActorEnum::ACTOR2:
			m_btnCombinationSelectDrawable[i]->setTexture(m_btnCombinationSelectTexture[1]);
			break;
		}
	}
}

void GameRoundDrawer::drawCombinationButtons()
{
	for (int i = 0; i < m_round->getDiceThrow().getCombinationCount(); i++)
	{
		m_btnCombinationSelectDrawable[i]->draw();
		m_btnCombinationSelectText[i]->draw();
	}
}
