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
#ifndef DEBUG
#include <doctest.h>
#include <memory>
#include "RandomBot.h"
#include "GreedyBot.h"
#include "logic/GameRound.h"
#include "util/MersenneTwister.h"

TEST_CASE("SmartBot wins over 75\% of the time") {
	const int maxGameRounds = 10000;
	double winRatioThreashold = 0.75;
	
	auto actor1 = std::make_shared<SmartBot>();
	
	SUBCASE("SmartBot vs Greedy Bot") {
		auto actor2 = std::make_shared<GreedyBot>();

		int winsSmartBot = 0;
		int winsGreedyBot = 0;

		for (int gamesCount = 0; gamesCount < maxGameRounds; gamesCount++)
		{
			MersenneTwister rand = MersenneTwister(gamesCount);
			GameRound gameRound(actor1, actor2, rand);
			while (!gameRound.isOver()) {
				gameRound.nextStep();
			}

			if (gameRound.getCurrentActorEnum() == ActorEnum::ACTOR1) {
				winsSmartBot++;
			} else {
				winsGreedyBot++;
			}
		}

		const double winRatio = (static_cast<double>(winsSmartBot)) / maxGameRounds;

		CHECK(winRatio > winRatioThreashold);
		INFO("The win ratio of SmartBot vs GreedyBot is:", winRatio);
	}

	SUBCASE("SmartBot vs RandomBot") {
		auto actor2 = std::make_shared<RandomBot>();

		int winsSmartBot = 0;
		int winsRandomBot = 0;

		for (int gamesCount = 0; gamesCount < maxGameRounds; gamesCount++)
		{
			MersenneTwister rand = MersenneTwister(gamesCount);
			GameRound gameRound(actor1, actor2, rand);
			while (!gameRound.isOver()) {
				gameRound.nextStep();
			}

			if (gameRound.getCurrentActorEnum() == ActorEnum::ACTOR1) {
				winsSmartBot++;
			} else {
				winsRandomBot++;
			}
		}

		const double winRatio = (static_cast<double>(winsSmartBot)) / maxGameRounds;

		CHECK((winRatio > winRatioThreashold));
		CHECK(winRatio == 0.);
	}
}

#endif
