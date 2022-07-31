#include "GameRound.h"
#include <stdexcept>

GameRound::GameRound(const std::shared_ptr<Actor>& actor1, const std::shared_ptr<Actor>& actor2)
	: m_actor1{actor1}, m_actor2{actor2}
{
	if (!m_actor1 || !m_actor2)
		throw std::runtime_error("GameRound::GameRound() - actors may not be nullptr");
}

const Board& GameRound::getBoard() { return m_board; }
ActorEnum GameRound::getCurrentActor() { return m_currentActor; }
bool GameRound::isOver() { return m_isOver; }

void GameRound::nextStep() {

}
