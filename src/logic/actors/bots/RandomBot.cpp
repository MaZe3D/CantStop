#include "RandomBot.h"
#include <random>
#include <doctest.h>

uint8_t RandomBot::choseCombination(const Board &board, const DiceThrow &diceThrow, MersenneTwister& rand) {
	uint8_t choice = rand.getRandomInt(diceThrow.getCombinationCount() - 1);
	return choice;
}

bool RandomBot::finishedTurn(const Board &board, MersenneTwister& rand) {
	return (rand.getRandomInt(1) == 1);
}

TEST_CASE("RandomBot") {
	MersenneTwister rand = MersenneTwister();
	ActorEnum actorEnum = ActorEnum::ACTOR1;
	RandomBot bot = RandomBot();
	
	SUBCASE("choseCombination"){
		Board board;
		board.stringToBoard(
			"actor1Marker 2 2 2 2 2 2 2 2 2 2 2"
			"actor2Marker 2 2 2 2 2 2 2 2 2 2 2"
			"RunnerOffset 0 0 0 0 0 0 0 0 0 0 0"
		);
		auto diceThrow = DiceThrow(board, actorEnum, rand);
		auto combination = bot.choseCombination(board, diceThrow, rand);
		CHECK((combination >= 0 && combination < 6));
	}

	SUBCASE("finishedTurn") {
		Board board;
		board.stringToBoard(
			"actor1Marker 2 2 2 2 2 2 2 2 2 2 2"
			"actor2Marker 2 2 2 2 2 2 2 2 2 2 2"
			"RunnerOffset 0 0 0 0 0 0 0 0 0 0 0"
		);
		auto diceThrow = DiceThrow(board, actorEnum, rand);
		auto finished = bot.finishedTurn(board, rand);
		CHECK((finished == true || finished == false));
	}
}