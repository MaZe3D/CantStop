#pragma once
#include "../Actor.h"

class SmartBot : public Actor {
    SmartBot();
    uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) override;
    bool finishedTurn(const Board& board) override;
};
