#pragma once
#include "../Bot.h"

class GreedyBot : public Bot {
    GreedyBot();
    uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) override;
    bool finishedTurn(const Board& board) override;
};
