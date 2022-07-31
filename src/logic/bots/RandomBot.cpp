#include "RandomBot.h"
#include <random>

RandomBot::RandomBot() {}

uint8_t RandomBot::choseCombination(const Board &board, const DiceThrow &diceThrow) {
    uint8_t choice = rand() % diceThrow.m_combinations.size() + 1;
    return choice;
}

bool RandomBot::finishedTurn(const Board &board) {
    return (rand() % 2 == 1);
}
