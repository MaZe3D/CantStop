#include "SafeBot.h"
#include <list>
#include <doctest.h>

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
		if (if combination.b > 0 && board.getColumn(combination.b - 2).runnerOffset != 0) tempRating++;
		if (tempRating > rating) {
			bestCombination = i;
			rating = tempRating;
		}
		i++;
	}
	return bestCombination;
}

TEST_CASE("SafeBot") {
	MersenneTwister rand = MersenneTwister(0);
	SafeBot bot;
	SUBCASE("choseCombination") {
		Board board;
		auto diceThrow = DiceThrow(board, ActorEnum::ACTOR1, rand);
		board.stringToBoard(
			"actor1Marker 2 2 2 2 2 2 2 2 2 2 2"
			"actor2Marker 2 2 2 2 2 2 2 2 2 2 2"
			"RunnerOffset 0 0 0 0 0 1 0 0 0 0 0"
		);
		CHECK(bot.choseCombination(board, diceThrow, rand) == 0);
		board.stringToBoard(
			"actor1Marker 2 2 2 2 2 2 2 2 2 2 2"
			"actor2Marker 2 2 2 2 2 2 2 2 2 2 2"
			"RunnerOffset 0 0 0 0 0 0 2 0 0 0 0"
		);
		CHECK(bot.choseCombination(board, diceThrow, rand) == 1);
	}
	SUBCASE("finishedTurn") {
		Board board;
		board.stringToBoard(
			"actor1Marker 2 2 2 2 2 2 2 2 2 2 2"
			"actor2Marker 2 2 2 2 2 2 2 2 2 2 2"
			"RunnerOffset 0 0 0 0 0 1 0 0 0 0 0"
		);
		CHECK(!bot.finishedTurn(board, rand));

		board.stringToBoard(
			"actor1Marker 2 2 2 2 2 2 2 2 2 2 2"
			"actor2Marker 2 2 2 2 2 2 2 2 2 2 2"
			"RunnerOffset 0 2 0 0 0 1 2 0 0 0 0"
		);
		CHECK(bot.finishedTurn(board, rand));
	}

}
