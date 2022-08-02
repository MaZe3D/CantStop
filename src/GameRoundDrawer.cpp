#include "GameRoundDrawer.h"
#include "logic/actors/Player.h"
#include "logic/actors/Bot.h"
#include "Game.h"
#include "util/log.h"

GameRoundDrawer::GameRoundDrawer(const std::shared_ptr<Window> window, Game& game, const std::shared_ptr<const Font>& font)
	: Event(window)
	, m_game(game)
	, m_background("res/sprites/Game_Background.png", window)
	, m_menuButtonText(font, " menu", window)
	, m_textureBarPlayer1(window->loadTexture("res/sprites/Game_Player1_Bar.png"))
	, m_textureBarPlayer2(window->loadTexture("res/sprites/Game_Player2_Bar.png"))
	, m_textureBarTemp(window->loadTexture("res/sprites/Game_Temp_Bar.png"))
	, m_victoryText(font, "click here to continue", window)
	, m_btnCombinationSelectFrame {
		TextureDrawable("res/sprites/Game_Player1_SelectFrame.png", window),
		TextureDrawable("res/sprites/Game_Player2_SelectFrame.png", window)
	}
{
	WindowEvent::unsubscribe();
	ClickEvent::unsubscribe();
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

	m_btnCombinationSelectFrame[0].rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_btnCombinationSelectFrame[1].rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	for (int i = 0; i < 6; i++) {
		m_btnCombinationSelectText[i] = std::make_shared<TextDrawable>(font, " ", window);
		m_btnCombinationSelectText[i]->rect
			.setAnchorModeX(Rect::AnchorMode::CENTER)
			.setAnchorModeY(Rect::AnchorMode::CENTER);
	}

	for (int i = 0; i < 6; i++) {
		m_btnCombinationSelectDrawable.push_back(std::make_shared<TextureDrawable>(m_btnCombinationSelectTexture[0]));
	}

	m_stopText     = std::make_shared<TextDrawable>(font, "Stop"    , window);
	m_continueText = std::make_shared<TextDrawable>(font, "Continue", window);
	m_stopText    ->rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);
	m_continueText->rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::CENTER);

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
	if (std::dynamic_pointer_cast<Bot>(m_round->getCurrentActor()) && m_round->getNextStep() == GameRound::NextStep::CHOOSE_DICE_COMBINATION) {
		m_round->nextStep();
	}
	WindowEvent::subscribe();
	ClickEvent::subscribe();
	setBars();
	setDiceTextures();
	updateCombinationButtons();
	onWindowResized(m_window->getWidth(), m_window->getHeight());
}

void GameRoundDrawer::draw() {
	m_background.draw();
	m_menuButtonText.draw();

	for(auto &bars : m_bars) {
		bars.draw();
	}

	for (int i = 0; i < 4; i++) {
		m_diceTextureDrawable[i].draw();
	}

	drawCombinationButtons();

	if (m_round->getNextStep() == GameRound::NextStep::CHOOSE_TO_CONTINUE_OR_STOP) {
		m_continueText->draw();
		if (std::dynamic_pointer_cast<Player>(m_round->getCurrentActor())) {
			m_stopText->draw();
		}
	}
	else if (m_round->getDiceThrow().getCombinationCount() == 0 || std::dynamic_pointer_cast<Bot>(m_round->getCurrentActor())) {
		m_continueText->draw();
	}

	if (m_round->isOver()) {
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
	m_menuButtonText.rect.setHeightKeepAspect(height/20, m_menuButtonText.getTexture()->getAspect());
	m_menuButtonText.rect.setPosX(width/2-height*16/9/2);

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
	const double btnCombinationDistance = (1./10) * btnCombinationHight;

	for(int i = 0; i < 6; i++) {
		m_btnCombinationSelectDrawable[i]->rect
			.setPos(m_diceTextureDrawable[(m_round->getCurrentActorEnum() == ActorEnum::ACTOR1) ? 3 : 0].rect.getPosX(), m_diceTextureDrawable[0].rect.getPosY() + 1.5 * m_diceTextureDrawable[0].rect.getHeight() + i * (btnCombinationHight + btnCombinationDistance))
			.setWidthKeepAspect(std::abs(m_diceTextureDrawable[0].rect.getPosX() - m_diceTextureDrawable[3].rect.getPosX()), m_btnCombinationSelectDrawable[i]->getTexture()->getAspect());
		m_btnCombinationSelectText[i]->rect
			.setPos(m_btnCombinationSelectDrawable[i]->rect.getPosX() + (m_btnCombinationSelectDrawable[i]->rect.getWidth()/2)
				, m_btnCombinationSelectDrawable[i]->rect.getPosY() + (m_btnCombinationSelectDrawable[i]->rect.getHeight()/2))
			.setHeightKeepAspect(m_btnCombinationSelectDrawable[i]->rect.getHeight()/2, m_btnCombinationSelectText[i]->getTexture()->getAspect());
	}
	if (m_round->getNextStep() == GameRound::NextStep::CHOOSE_TO_CONTINUE_OR_STOP) {
		const Rect& rect = m_btnCombinationSelectText[m_round->getChosenCombinationID()]->rect;
		uint8_t actor = (m_round->getCurrentActorEnum() == ActorEnum::ACTOR1) ? 0 : 1;
		m_btnCombinationSelectFrame[actor].rect.setPos(rect.getPosX(), rect.getPosY());
		m_btnCombinationSelectFrame[actor].rect.setHeightKeepAspect(1.2*m_btnCombinationSelectDrawable[0]->rect.getHeight(), m_btnCombinationSelectFrame[actor].getTexture()->getAspect());
		m_btnCombinationSelectFrame[(actor+1)&1].rect.setDimensions(0, 0);
	} else {
		m_btnCombinationSelectFrame[0].rect.setDimensions(0, 0);
		m_btnCombinationSelectFrame[1].rect.setDimensions(0, 0);
	}

	const Rect& rect = m_btnCombinationSelectText[5]->rect;
	m_stopText    ->rect.setPos(rect.getPosX(), rect.getPosY()+btnCombinationHight*5/2);
	m_continueText->rect.setPos(rect.getPosX(), rect.getPosY()+btnCombinationHight*3/2);
	m_stopText    ->rect.setHeightKeepAspect(btnCombinationHight*2/3, m_stopText    ->getTexture()->getAspect());
	m_continueText->rect.setHeightKeepAspect(btnCombinationHight*2/3, m_continueText->getTexture()->getAspect());

	m_diceTextureDrawable[(m_round->getCurrentActorEnum() == ActorEnum::ACTOR1) ? 3 : 0].rect.getPosX();

	m_victoryDrawable->rect
		.setHeightKeepAspect(height, m_victoryDrawable->getTexture()->getAspect())
		.setPos(width / 2., height / 2);

	m_victoryText.rect.setHeightKeepAspect(height*(70./2160.), m_victoryText.getTexture()->getAspect())
		.setPos(width / 2., height * (2033./2160.));
}

void GameRoundDrawer::onLeftClick(int32_t x, int32_t y) {
	if (!m_round) return;
	if (m_round->isOver()) {
		if (m_victoryText.rect.containsPoint(x, y)) {
			WindowEvent::unsubscribe();
			ClickEvent::unsubscribe();
			m_round = nullptr;
			m_game.showMenu();
		}
		return;
	}
	else if (m_menuButtonText.rect.containsPoint(x, y)) {
		WindowEvent::unsubscribe();
		ClickEvent::unsubscribe();
		m_round = nullptr;
		m_game.showMenu();
		return;
	}

	std::shared_ptr<Actor> actor = m_round->getCurrentActor();
	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(actor);

	if (player) {
		if (m_round->getNextStep() == GameRound::NextStep::CHOOSE_DICE_COMBINATION) {
			bool combinationSelected = false;
			if (m_round->getDiceThrow().getCombinationCount() == 0 && m_continueText->rect.containsPoint(x, y)) {
				combinationSelected = true;
			}
			for (uint8_t i = 0; i < m_round->getDiceThrow().getCombinationCount(); i++) {
				if (m_btnCombinationSelectDrawable[i]->rect.containsPoint(x, y)) {
					player->setReturnValueForChooseCombination(i);
					combinationSelected = true;
					break;
				}
			}
			if (!combinationSelected) return;
		}
		else {
			if (m_stopText->rect.containsPoint(x, y)) {
				player->setReturnValueForFinishedTurn(true);
			}
			else if (m_continueText->rect.containsPoint(x, y)) {
				player->setReturnValueForFinishedTurn(false);
			}
			else return;
		}
	}
	else if (!m_continueText->rect.containsPoint(x, y)) return;

	if (!m_round->isOver()) {
		m_round->nextStep();
		if (m_round->getNextStep() == GameRound::NextStep::CHOOSE_DICE_COMBINATION && std::dynamic_pointer_cast<Bot>(m_round->getCurrentActor())) {
			m_round->nextStep();
		}
	}
	
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
	m_btnCombinationSelectFrame[0].draw();
	m_btnCombinationSelectFrame[1].draw();
}
