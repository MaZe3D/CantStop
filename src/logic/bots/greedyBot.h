#pragma once
#include "../Actor.h"

class greedyBot : public Actor{
    greedyBot();
    uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) override;
    bool finishedTurn(const Board& board) override;
};