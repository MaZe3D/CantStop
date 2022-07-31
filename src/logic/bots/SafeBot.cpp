#include "SafeBot.h"
#include <list>

bool SafeBot::finishedTurn(const Board &board) {
    uint8_t usedMarkers = 0;
    for (int i = 0; i < 11; ++i) {
        if (board.getColumn(i).runnerOffset != 0) {
            usedMarkers++;
        }
    }
    return (usedMarkers == 3);
}

uint8_t SafeBot::choseCombination(const Board &board, const DiceThrow &diceThrow) {
    uint8_t bestCombination = 0;
    uint8_t rating = 0;
    uint8_t i = 0;
    for (DiceThrow::Combination combination : diceThrow.m_combinations) {
        uint8_t tempRating = 0;
        if (board.getColumn(combination.a - 2).runnerOffset != 0) tempRating++;
        if (board.getColumn(combination.b - 2).runnerOffset != 0) tempRating++;
        if (tempRating > rating) {
            bestCombination = i;
            rating = tempRating;
        }
        i++;
    }
    return bestCombination;
}