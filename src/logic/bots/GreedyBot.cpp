#include "GreedyBot.h"

GreedyBot::GreedyBot() {}

bool GreedyBot::finishedTurn(const Board &board) {
	for (uint8_t i = 0; i < 11; i++) {
		if (board.getColumn(i).runnerOffset != 0) {
			const uint8_t& actorMarker = (this->getActorEnum() == ActorEnum::ACTOR1) ? board.getColumn(i).actor1Marker : board.getColumn(i).actor2Marker;
			if ((board.getColumn(i).runnerOffset + actorMarker) == board.getColumnHeight(i)) {
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
		const uint8_t& actorMarker = (this->getActorEnum() == ActorEnum::ACTOR1) ? board.getColumn(i).actor1Marker : board.getColumn(i).actor2Marker;
		if (board.getColumnHeight(i) > actorMarker) {
			if (board.getColumnHeight(i) - actorMarker < diffrence) {
				bestCombination = i;
				diffrence = board.getColumnHeight(i) - actorMarker;
			}
		}
	}
	return bestCombination;
}
