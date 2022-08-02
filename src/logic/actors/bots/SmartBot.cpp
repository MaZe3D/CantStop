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
				(2*board.getColumn(combination.b - 2).maxHeight-distanceB)/2);
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
	/*
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
	return choice;*/
}

bool SmartBot::finishedTurn(const Board& board, MersenneTwister& rand) {
	uint8_t usedMarkers = 0;
	uint8_t riskfactor = 0;
	uint8_t weight = 0;
	for (int i = 0; i < 11; i++) {
		if (board.getColumn(i).runnerOffset > 0) {
			usedMarkers++;
			weight += board.getColumn(i).maxHeight;
			riskfactor += board.getColumn(i).runnerOffset;
		}
	}
	if(usedMarkers != 3) {
		return false;
	}
	else if (weight < 15) {
		return true;
	}
	else if(riskfactor > 9) {
		return true;
	}
	else if(weight < 24 && riskfactor > 6) {
		return true;
	}
	else if (weight > 30) {
		return false;
	}
	else {
		return true;
	}
}
