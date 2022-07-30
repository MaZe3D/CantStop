#pragma once
#include "../Actor.h"

class intelligentBot : public Actor{
    uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) override;
    bool finishedTurn(const Board& board) override;
};
