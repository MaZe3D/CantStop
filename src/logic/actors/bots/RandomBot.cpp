#include "RandomBot.h"
#include <random>

uint8_t RandomBot::choseCombination(const Board &board, const DiceThrow &diceThrow, MersenneTwister& rand) {
	uint8_t choice = rand.getRandomInt(diceThrow.getCombinationCount() - 1);
	return choice;
}

bool RandomBot::finishedTurn(const Board &board, MersenneTwister& rand) {
	return (rand.getRandomInt(1) == 1);
}
