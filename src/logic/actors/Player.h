#pragma once
#include "../Actor.h"

class Player: public Actor {
public:
	Player();
    uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) override;
    bool finishedTurn(const Board& board) override;
};
