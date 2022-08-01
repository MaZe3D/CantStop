#include "SafeBot.h"
#include <list>

bool SafeBot::finishedTurn(const Board &board, MersenneTwister& rand) {
	uint8_t usedMarkers = 0;
	for (int i = 0; i < 11; ++i) {
		if (board.getColumn(i).runnerOffset != 0) {
			usedMarkers++;
		}
	}
	return (usedMarkers == 3);
}

uint8_t SafeBot::choseCombination(const Board &board, const DiceThrow &diceThrow, MersenneTwister& rand) {
	uint8_t bestCombination = 0;
	uint8_t rating = 0;
	uint8_t i = 0;
	for (uint8_t combinationID = 0; combinationID < diceThrow.getCombinationCount(); combinationID++) {
		uint8_t tempRating = 0;
		const DiceThrow::Combination& combination = diceThrow.getCombination(combinationID);
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
