#include "GreedyBot.h"

bool GreedyBot::finishedTurn(const Board &board) {
	for (uint8_t i = 0; i < 11; i++) {
		const Board::Column& column = board.getColumn(i);
		if (column.runnerOffset != 0) {
			const uint8_t& actorMarker = (this->getActorEnum() == ActorEnum::ACTOR1) ? column.actor1Marker : column.actor2Marker;
			if ((column.runnerOffset + actorMarker) == column.maxHeight) {
				return true;
			}
		}
	}
	return false;
}

uint8_t GreedyBot::choseCombination(const Board &board, const DiceThrow &diceThrow) {
	uint8_t bestCombination = 0;
	uint8_t minDifference = 20;
	for (int i = 0; i < diceThrow.getCombinationCount(); i++) {
		const auto& combination = diceThrow.getCombination(i);
		const Board::Column& columnA = board.getColumn(combination.a-2);
		uint8_t actorMarker = (this->getActorEnum() == ActorEnum::ACTOR1) ? columnA.actor1Marker : columnA.actor2Marker;
		actorMarker += columnA.runnerOffset;
		if (columnA.maxHeight - actorMarker < minDifference) {
			bestCombination = i;
			minDifference = columnA.maxHeight - actorMarker - 1;
		}
		if(combination.b < 0) continue;
		const Board::Column& columnB = board.getColumn(combination.b-2);
		actorMarker = (this->getActorEnum() == ActorEnum::ACTOR1) ? columnB.actor1Marker : columnB.actor2Marker;
		actorMarker += columnB.runnerOffset;
		if (columnB.maxHeight - actorMarker < minDifference) {
			bestCombination = i;
			minDifference = columnB.maxHeight - actorMarker - 1;
		}
		if(combination.a == combination.b){
			if (columnB.maxHeight - actorMarker < minDifference) {
				bestCombination = i;
				minDifference = columnB.maxHeight - actorMarker - 2;
			}
		}
	}
	return bestCombination;
}
