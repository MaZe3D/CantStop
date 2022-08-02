#include <cmath>
#include <stdexcept>
#include "Board.h"
#include <regex>
#include <iostream>
#include <string>
#include <iterator>
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

/* The string needs to be like following:
"actor1Marker 2 3 4 5 6 7 8 9 10 11 12"
"actor2Marker 2 3 4 5 6 7 8 9 10 11 12"
"RunnerOffset 0 0 0 0 0 0 0 0 0 0 0";
 */
void Board::stringToBoard(std::string boardString) {
	std::regex indices ("actor1Marker|actor2Marker|RunnerOffset");
	std::string formattedString = std::regex_replace(boardString, indices, "");

	std::regex columnRegex (R"(\d\d|\d)");
	uint8_t iterations = 0;
	auto formattedStringBegin = std::sregex_iterator(formattedString.begin(), formattedString.end(), columnRegex);
	auto formattedStringEnd = std::sregex_iterator();
	for (auto it = formattedStringBegin; it != formattedStringEnd; ++it) {
		std::smatch match = *it;
		uint8_t marker = std::stoi(match.str());
		if(iterations <=10)
			m_columns[iterations].actor1Marker = marker;
		else if(iterations <=21)
			m_columns[iterations - 11].actor2Marker = marker;
		else if(iterations <=32)
			m_columns[iterations - 22].runnerOffset = marker;
		iterations++;
	}
	if (iterations != 33) throw std::runtime_error("Board::stringToBoard() - invalid board string");
}
TEST_CASE("strintToBoard") {
	Board board;
	std::string boardString = 
	"actor1Marker 0 1 4 6 1 12 10 1 0 3 2"
	"actor2Marker 3 2 7 1 11 0 1 6 7 0 0"
	"RunnerOffset 1 0 0 0 5 0 0 0 0 0 2";

	board.stringToBoard(boardString);
	SUBCASE("Check actormarkers") {
		CHECK(board.getColumn(0).actor1Marker == 0);
		CHECK(board.getColumn(10).actor1Marker == 2);
		CHECK(board.getColumn(5).actor1Marker == 12);
		CHECK(board.getColumn(0).actor2Marker == 3);
		CHECK(board.getColumn(10).actor2Marker == 0);
		CHECK(board.getColumn(4).actor2Marker == 11);
	}
	SUBCASE("Check runnerOffsets") {
		CHECK(board.getColumn(0).runnerOffset == 1);
		CHECK(board.getColumn(10).runnerOffset == 2);
		CHECK(board.getColumn(4).runnerOffset == 5);
		CHECK(board.getColumn(1).runnerOffset == 0);
		CHECK(board.getColumn(9).runnerOffset == 0);
		CHECK(board.getColumn(3).runnerOffset == 0);
	}
	SUBCASE("Check faulty boardString") {
		std::string faultyBoardString ={
			"actor1Marker 0 1 4 6 1 12 10 1 0 3 2"
			"actor2Marker 3 2 7 1 11 0 1 6 7 0 0"
		};
		CHECK_THROWS(board.stringToBoard(faultyBoardString));
		std::string faultyBoardString1 ={
			"actor1Marker 0 1 4 6 1 12 10 1 0 3 2"
			"actor2Marker 3 2 7 1 11 0 1 6 7 0 0"
			"3 2 7 1 11 0 1 6 7 0 0 0 0 0 0 0 0"
		};
		CHECK_THROWS(board.stringToBoard(faultyBoardString1));
		std::string faultyBoardString2 ={
			"actor1Marker 0 1 4 6 1 12 10 1 0 3 2"
			"actor2Marker 3 2 7 1 11 0 1 6 7 0 0"
			"RunnerOffset 1 0 0 0 5 0 0 0 0 0 0 2 0"
		};
		CHECK_THROWS(board.stringToBoard(faultyBoardString2));
	}
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

		Board b;
		b.stringToBoard(
			"actor1Marker 0 1 4 6  1 12 10 1 0 3 2"
			"actor2Marker 3 2 7 1 11  0  1 6 7 0 0"
			"RunnerOffset 1 0 0 0  5  0  0 1 0 0 0"
		);
		b.advanceRunnerMarkers(DiceThrow::Combination{3, 6});
		CHECK(b.getColumn(0).runnerOffset == 1);
		CHECK(b.getColumn(1).runnerOffset == 1);
		CHECK(b.getColumn(2).runnerOffset == 0);
		CHECK(b.getColumn(3).runnerOffset == 0);
		CHECK(b.getColumn(4).runnerOffset == 6);
		CHECK(b.getColumn(10).runnerOffset == 0);
		/* for (int i = 0; i < b.getColumn(5).maxHeight; i++) {
			b.advanceRunnerMarkers(combination);
			CHECK(b.getColumn(5).runnerOffset == i);
		
		} */
	}
	SUBCASE("Check for correct actorMarkers application") {
		Board b;
		b.stringToBoard(
			"actor1Marker 0 1 4 6  1 12 10 1 0 3 2"
			"actor2Marker 3 2 7 1  3  0  1 6 0 0 0"
			"RunnerOffset 1 0 0 0  5  0  0 0 0 0 1"
		);
		CHECK(b.applyRunnerOffsetsToActorMarkersAndCheckWin(ActorEnum::ACTOR1) == false);
		b.stringToBoard(
			"actor1Marker 0 1 4 6  1 12 10 1 0 3 2"
			"actor2Marker 3 2 7 1 10  0  1 6 0 0 0"
			"RunnerOffset 1 0 0 0  5  0  0 0 0 0 1"
		);
		CHECK(b.applyRunnerOffsetsToActorMarkersAndCheckWin(ActorEnum::ACTOR2) == true);
		
		CHECK( (b.getColumn(0).actor1Marker == 0 
			&& b.getColumn(1).actor1Marker == 1
			&& b.getColumn(2).actor1Marker == 4
			&& b.getColumn(3).actor1Marker == 6
			&& b.getColumn(4).actor1Marker == 1
			&& b.getColumn(5).actor1Marker == 12
			&& b.getColumn(6).actor1Marker == 10
			&& b.getColumn(7).actor1Marker == 1
			&& b.getColumn(8).actor1Marker == 0
			&& b.getColumn(9).actor1Marker == 3
			&& b.getColumn(10).actor1Marker == 2)
		);
		CHECK( (b.getColumn(0).actor2Marker == 3
			&& b.getColumn(1).actor2Marker == 2
			&& b.getColumn(2).actor2Marker == 7
			&& b.getColumn(3).actor2Marker == 1
			&& b.getColumn(4).actor2Marker == 11
			&& b.getColumn(5).actor2Marker == 0
			&& b.getColumn(6).actor2Marker == 1
			&& b.getColumn(7).actor2Marker == 6
			&& b.getColumn(8).actor2Marker == 0
			&& b.getColumn(9).actor2Marker == 0
			&& b.getColumn(10).actor2Marker == 1 )
		);
	}
}
