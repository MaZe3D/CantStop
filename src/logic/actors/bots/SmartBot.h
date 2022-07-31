#pragma once
#include "../Bot.h"

class SmartBot : public Bot {
    SmartBot();
    uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) override;
    bool finishedTurn(const Board& board) override;
};
