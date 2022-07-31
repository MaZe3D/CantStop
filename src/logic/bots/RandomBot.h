#pragma once
#include "../Actor.h"

class RandomBot : public Actor {
public:
    RandomBot();
    uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) override;
    bool finishedTurn(const Board& board) override;
};