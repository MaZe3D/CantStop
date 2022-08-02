#include <cmath>
#include <stdexcept>
#include "Board.h"
#include <doctest.h>

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

TEST_CASE("Board") {
    Board b;
    SUBCASE("Check height of columns") {
        CHECK(b.getColumn(0).maxHeight == 3);
        CHECK(b.getColumn(1).maxHeight == 5);
        CHECK(b.getColumn(2).maxHeight == 7);
        CHECK(b.getColumn(3).maxHeight == 9);
        CHECK(b.getColumn(4).maxHeight == 11);
        CHECK(b.getColumn(5).maxHeight == 13);
        CHECK(b.getColumn(6).maxHeight == 11);
        CHECK(b.getColumn(7).maxHeight == 9);
        CHECK(b.getColumn(8).maxHeight == 7);
        CHECK(b.getColumn(9).maxHeight == 5);
        CHECK(b.getColumn(10).maxHeight == 3);
    }

    SUBCASE("Check for empty Columns") {
        for (int i = 0; i < 11; ++i) {
            CHECK(b.getColumn(i).runnerOffset == 0);
            CHECK(b.getColumn(i).actor1Marker == 0);
            CHECK(b.getColumn(i).actor2Marker == 0);
        }
    }

	SUBCASE("Check for correct AdvanceRunnerMarkers") {
		DiceThrow::Combination combination;
		Board b;
		for (int i = 0; i < 4; ++i) {
			combination.a = 2 + i;
			combination.b = 12 - i;
			for (int j = 0; j < b.getColumn(i).maxHeight; j++) {
				b.advanceRunnerMarkers(combination);
				CHECK(b.getColumn(i).runnerOffset == j);
				CHECK(b.getColumn(11 - i).runnerOffset == j);
			}
		}
		combination.a = 7;
		for (int i = 0; i < b.getColumn(5).maxHeight; i++) {
			b.advanceRunnerMarkers(combination);
			CHECK(b.getColumn(5).runnerOffset == i);
		}
	}
}
