#pragma once
#include "../Bot.h"

class RandomBot : public Bot {
public:
	uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) override;
	bool finishedTurn(const Board& board) override;
};
