#include "Board.h"
#include <cmath>

void Board::resetRunnerOffsets() {
	for (Column& column : m_columns) {
		column.runnerOffset = 0;
	}
}

bool Board::applyRunnerOffsetsToActorMarkersAndCheckWin(const ActorEnum actor) {
	int fullColumns = 0;
	for (int i = 0; i < 11; i++) {
		int columnHeight = getColumnHeight(i);
		uint8_t& actorMarker = (actor == ActorEnum::ACTOR1) ? m_columns[i].actor1Marker : m_columns[i].actor2Marker;
		if (actorMarker + m_columns[i].runnerOffset >= columnHeight) {
			actorMarker = columnHeight;
			fullColumns++;
		} else {
			actorMarker += m_columns[i].runnerOffset;
		}
	}
	resetRunnerOffsets();
	return (fullColumns >= 3);
}

void Board::advanceRunnerMarkers(const DiceThrow::Combination &combination) {
	if (combination.a > 1) m_columns[(combination.a - 2)].runnerOffset++;
	if (combination.b > 1) m_columns[(combination.b - 2)].runnerOffset++;
}

const Board::Column& Board::getColumn(uint8_t column) const {
	return m_columns[column];
}

const uint8_t Board::getColumnHeight(uint8_t column) const {
	return (12 - std::abs(7 - (column + 2)) * 2 + 1);
}