#include "GameRound.h"
#include <stdexcept>

GameRound::GameRound(const std::shared_ptr<Actor>& actor1, const std::shared_ptr<Actor>& actor2)
	: m_actor1{actor1}
	, m_actor2{actor2}
	, m_diceThrow(m_board, m_currentActor)
{
	if (!m_actor1 || !m_actor2)
		throw std::runtime_error("GameRound::GameRound() - actors may not be nullptr");
	m_actor1->setActorEnum(ActorEnum::ACTOR1);
	m_actor2->setActorEnum(ActorEnum::ACTOR2);
}

const Board& GameRound::getBoard() const {
	return m_board;
}

ActorEnum GameRound::getCurrentActorEnum() const {
	return m_currentActor;
}

std::shared_ptr<Actor> GameRound::getCurrentActor() const {
	return getActor(m_currentActor);
}

std::shared_ptr<Actor> GameRound::getActor(ActorEnum actor) const {
	return (actor == ActorEnum::ACTOR1) ? m_actor1 : m_actor2;
}

const DiceThrow& GameRound::getDiceThrow() const {
	return m_diceThrow;
}

uint8_t GameRound::getChosenCombinationID() const {
	return m_chosenCombinationID;
}

bool GameRound::isOver() const {
	return m_isOver;
}

GameRound::NextStep GameRound::getNextStep() const {
	return m_nextStep;
}

void GameRound::nextStep() {
	if (m_isOver) throw std::runtime_error("GameRound::nextStep() - game is over!");
	std::shared_ptr<Actor>& currentActor = (m_currentActor == ActorEnum::ACTOR1) ? m_actor1 : m_actor2;
	
	switch (m_nextStep) {
	case (NextStep::CHOOSE_DICE_COMBINATION):
		if (m_diceThrow.getCombinationCount() == 0) {
			m_board.resetRunnerOffsets();
			m_currentActor = (m_currentActor == ActorEnum::ACTOR1) ? ActorEnum::ACTOR2 : ActorEnum::ACTOR1;
			m_diceThrow = DiceThrow(m_board, m_currentActor);
			break;
		}
		m_chosenCombinationID = currentActor->choseCombination(m_board, m_diceThrow);
		m_board.advanceRunnerMarkers(m_diceThrow.getCombination(m_chosenCombinationID));
		m_nextStep = NextStep::CHOOSE_TO_CONTINUE_OR_STOP;
		break;
	case (NextStep::CHOOSE_TO_CONTINUE_OR_STOP):
		if (currentActor->finishedTurn(m_board)) {
			if ((m_isOver = m_board.applyRunnerOffsetsToActorMarkersAndCheckWin(m_currentActor))) return;
			m_currentActor = (m_currentActor == ActorEnum::ACTOR1) ? ActorEnum::ACTOR2 : ActorEnum::ACTOR1;
		}
		m_nextStep = NextStep::CHOOSE_DICE_COMBINATION;
		m_diceThrow = DiceThrow(m_board, m_currentActor);
		break;
	}
}
