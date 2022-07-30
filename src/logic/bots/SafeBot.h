#pragma once
#include "../Actor.h"

class safeBot : public Actor {
    safeBot();
    uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) override;
    bool finishedTurn(const Board& board) override;
};
