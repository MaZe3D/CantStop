#include "GameRound.h"
#include <stdexcept>

GameRound::GameRound(const std::shared_ptr<Actor>& actor1, const std::shared_ptr<Actor>& actor2)
	: m_actor1{actor1}
	, m_actor2{actor2}
	, m_diceThrow(m_board, m_currentActor)
{
	if (!m_actor1 || !m_actor2)
		throw std::runtime_error("GameRound::GameRound() - actors may not be nullptr");
}

const Board& GameRound::getBoard() { return m_board; }
ActorEnum GameRound::getCurrentActor() { return m_currentActor; }
const DiceThrow& GameRound::getDiceThrow() { return m_diceThrow; }
bool GameRound::isOver() { return m_isOver; }

GameRound::NextStep GameRound::getNextStep() {
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
		m_board.advanceRunnerMarkers(m_diceThrow.getCombination(currentActor->choseCombination(m_board, m_diceThrow)));
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
