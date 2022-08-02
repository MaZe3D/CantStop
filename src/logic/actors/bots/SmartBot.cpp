#include "SmartBot.h"


uint8_t SmartBot::choseCombination(const Board& board, const DiceThrow& diceThrow, MersenneTwister& rand) {
	uint8_t bestCombination = 0;
	float rating = 0;
	uint8_t i = 0;
	uint8_t distanceA = 0;
	uint8_t distanceB = 0;
	for (uint8_t combinationID = 0; combinationID < diceThrow.getCombinationCount(); combinationID++) {
		float tempRating = 0;
		const DiceThrow::Combination& combination = diceThrow.getCombination(combinationID);
		if(this->getActorEnum() == ActorEnum::ACTOR1){
			distanceA = board.getColumn(combination.a - 2).maxHeight - board.getColumn(combination.a - 2).actor1Marker - board.getColumn(combination.a - 2).runnerOffset;
			if(combination.b > 0) distanceB = board.getColumn(combination.b - 2).maxHeight - board.getColumn(combination.b - 2).actor1Marker - board.getColumn(combination.b - 2).runnerOffset;
		} else {
			distanceA = board.getColumn(combination.a - 2).maxHeight - board.getColumn(combination.a - 2).actor2Marker - board.getColumn(combination.a - 2).runnerOffset;
			if(combination.b > 0)distanceB = board.getColumn(combination.b - 2).maxHeight - board.getColumn(combination.b - 2).actor2Marker - board.getColumn(combination.b - 2).runnerOffset;
		}
		if(combination.a != -1 && combination.b != -1) {
				tempRating = ((2*board.getColumn(combination.a - 2).maxHeight-distanceA) + 
				(2*board.getColumn(combination.b - 2).maxHeight-distanceB)/2) + 1;
		}
		if(combination.b == -1) {
			tempRating = (2 * board.getColumn(combination.a - 2).maxHeight - distanceA);
		}
		if(tempRating > rating) {
			bestCombination = i;
			rating = tempRating;
		}
		i++;
	}
	return bestCombination;
}

bool SmartBot::finishedTurn(const Board& board, MersenneTwister& rand) {
	uint8_t usedMarkers = 0;
	uint8_t riskfactor = 0;
	uint8_t weight = 0;
	bool finished = false;
	for (int i = 0; i < 11; i++) {
		if (board.getColumn(i).runnerOffset > 0) {
			usedMarkers++;
			weight += board.getColumn(i).maxHeight;
			riskfactor += board.getColumn(i).runnerOffset;
			int marker = 0;
			if(this->getActorEnum() == ActorEnum::ACTOR1) marker = board.getColumn(i).actor1Marker;
			else marker = board.getColumn(i).actor2Marker;
			if(board.getColumn(i).maxHeight - board.getColumn(i).runnerOffset - marker == 0) {
				finished = true;
			}
		}
	}
	if(usedMarkers != 3) {
		return false;
	}
	else if(finished) {
		return true;
	}
	else if (weight < 11) {
		return true;
	}
	else if(riskfactor > 12) {
		return true;
	}
	else if(weight < 16 && riskfactor > 8) {
		return true;
	}
	else if (weight > 21) {
		return false;
	}
	else {
		return true;
	}
}
#ifndef DOCTEST_CONFIG_DISABLE
#include <doctest.h>
#include <memory>
#include "RandomBot.h"
#include "GreedyBot.h"
#include "SafeBot.h"
#include "logic/GameRound.h"
#include "util/MersenneTwister.h"

TEST_CASE("SmartBot wins over 75\% of the time") {
	const int maxGameRounds = 10000;
	double winRatioThreashold = 0.75;
	
	auto actor1 = std::make_shared<SmartBot>();
	
	/*SUBCASE("SmartBot vs Greedy Bot") {
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

			if (gameRound.getCurrentActorEnum() == actor1->getActorEnum()) {
				winsSmartBot++;
			} else {
				winsGreedyBot++;
			}
		}

		const double winRatio = (static_cast<double>(winsSmartBot)) / maxGameRounds;

		CHECK(winRatio > winRatioThreashold);
		INFO("The win ratio of SmartBot vs GreedyBot is:", winRatio);
	}*/

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

			if (gameRound.getCurrentActorEnum() == actor1->getActorEnum()) {
				winsSmartBot++;
			} else {
				winsRandomBot++;
			}
		}

		const double winRatio = (static_cast<double>(winsSmartBot)) / maxGameRounds;

		CHECK(winRatio > winRatioThreashold);
	}

	SUBCASE("SmartBot vs SaveBot") {
		auto actor2 = std::make_shared<SafeBot>();

		int winsSmartBot = 0;
		int winsRandomBot = 0;

		for (int gamesCount = 0; gamesCount < maxGameRounds; gamesCount++)
		{
			MersenneTwister rand = MersenneTwister(gamesCount);
			GameRound gameRound(actor1, actor2, rand);
			while (!gameRound.isOver()) {
				gameRound.nextStep();
			}

			if (gameRound.getCurrentActorEnum() == actor1->getActorEnum()) {
				winsSmartBot++;
			} else {
				winsRandomBot++;
			}
		}

		const double winRatio = (static_cast<double>(winsSmartBot)) / maxGameRounds;

		CHECK(winRatio > winRatioThreashold);
	}
}

#endif
