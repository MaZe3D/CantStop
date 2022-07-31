#include <cmath>
#include <stdexcept>
#include "Board.h"

Board::Board()
	: m_columns{0}
{
	for (uint8_t column = 0; column < 11; column++) {
		m_columns[column].maxHeight = (12 - std::abs(7 - (column + 2)) * 2 + 1);
	}
}

void Board::resetRunnerOffsets() {
	for (Column& column : m_columns) {
		column.runnerOffset = 0;
	}
}

bool Board::applyRunnerOffsetsToActorMarkersAndCheckWin(const ActorEnum actor) {
	int fullColumns = 0;
	for (int i = 0; i < 11; i++) {
		uint8_t& actorMarker = (actor == ActorEnum::ACTOR1) ? m_columns[i].actor1Marker : m_columns[i].actor2Marker;
		if (actorMarker + m_columns[i].runnerOffset >= m_columns[i].maxHeight) {
			actorMarker = m_columns[i].maxHeight;
			fullColumns++;
		} else {
			actorMarker += m_columns[i].runnerOffset;
		}
	}
	resetRunnerOffsets();
	return (fullColumns >= 3);
}

void Board::advanceRunnerMarkers(const DiceThrow::Combination &combination) {
	if (1 < combination.a && combination.a < 13) m_columns[combination.a - 2].runnerOffset++;
	if (1 < combination.b && combination.b < 13) m_columns[combination.b - 2].runnerOffset++;
}

const Board::Column& Board::getColumn(uint8_t column) const {
	if (column >= 11) throw std::runtime_error("Board::getColumn() - column must be < 11 " + std::to_string(column));
	return m_columns[column];
}
