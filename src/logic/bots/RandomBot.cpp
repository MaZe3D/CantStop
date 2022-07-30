#include "RandomBot.h"
#include <random>

randomBot::randomBot() {}

uint8_t randomBot::choseCombination(const Board &board, const DiceThrow &diceThrow) {
    uint8_t choice = rand() % diceThrow.m_combinations.size() + 1;
    return choice;
}

bool randomBot::finishedTurn(const Board &board) {
    return (rand() % 2 == 1);
}
