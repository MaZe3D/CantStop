#pragma once
#include "../Actor.h"

class Player: public Actor {
public:
	void setReturnValueForChooseCombination(uint8_t combination);
	void setReturnValueForFinishedTurn(bool finished);

	uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) override;
	bool finishedTurn(const Board& board) override;

private:
	uint8_t m_combination = 0;
	bool m_finished = true;
};
