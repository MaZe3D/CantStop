#include "SmartBot.h"

uint8_t SmartBot::choseCombination(const Board& board, const DiceThrow& diceThrow, MersenneTwister& rand) {
	uint8_t choice = 0;
	uint8_t distance = -1;
	for (int i = 0; i < diceThrow.getCombinationCount(); i++) {
		auto combination = diceThrow.getCombination(i);
		if (combination.a != -1 && combination.b != -1) {
			if ((7 - combination.a) + (7 - combination.b) < distance) {
				choice = i;
				distance = (7 - combination.a) + (7 - combination.b);
			}
		} else if (combination.a != -1) {
			if ((7 - combination.a) * 2 < distance) {
				choice = i;
				distance = (7 - combination.a) * 2;
			}
		} else if (combination.b != -1) {
			if ((7 - combination.b) * 2 < distance) {
				choice = i;
				distance = (7 - combination.b) * 2;
			}
		}
	}
	return choice;
}

bool SmartBot::finishedTurn(const Board& board, MersenneTwister& rand) {
	uint8_t usedMarkers = 0;
	for (int i = 0; i < 11; ++i) {
		if (board.getColumn(i).runnerOffset > 0) {
			usedMarkers++;
		}
	}
	return (usedMarkers == 3);
}
