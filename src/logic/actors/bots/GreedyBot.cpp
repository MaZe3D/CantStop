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
	uint8_t diffrence = 20;
	for (int i = 0; i < 11; i++) {
		const Board::Column& column = board.getColumn(i);
		const uint8_t& actorMarker = (this->getActorEnum() == ActorEnum::ACTOR1) ? column.actor1Marker : column.actor2Marker;
		if (column.maxHeight > actorMarker) {
			if (column.maxHeight - actorMarker < diffrence) {
				bestCombination = i;
				diffrence = column.maxHeight - actorMarker;
			}
		}
	}
	return bestCombination;
}
