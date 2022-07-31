#include "RandomBot.h"
#include <random>

uint8_t RandomBot::choseCombination(const Board &board, const DiceThrow &diceThrow) {
	uint8_t choice = rand() % diceThrow.getCombinationCount();
	return choice;
}

bool RandomBot::finishedTurn(const Board &board) {
	return (rand() % 2 == 1);
}
