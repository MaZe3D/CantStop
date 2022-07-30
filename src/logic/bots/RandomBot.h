#pragma once
#include "../Actor.h"

class randomBot : public Actor {
public:
    randomBot();
    uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) override;
    bool finishedTurn(const Board& board) override;
};