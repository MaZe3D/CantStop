#include "Player.h"

void Player::setReturnValueForChooseCombination(uint8_t combination) {
	m_combination = combination;
}

void Player::setReturnValueForFinishedTurn(bool finished) {
	m_finished = finished;
}

uint8_t Player::choseCombination(const Board& board, const DiceThrow& diceThrow, MersenneTwister& rand) {
	return m_combination;
}

bool Player::finishedTurn(const Board& board, MersenneTwister& rand) {
	return m_finished;
}
