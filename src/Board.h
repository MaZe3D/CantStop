#pragma once

#include "ActorEnum.h"
#include "DiceThrow.h"

class Board {
public:
	struct Column;

	Board();
	const Column& getColumn(uint8_t column) const;
	const uint8_t getColumnHeight(uint8_t column) const;
	void advanceRunnerMarkers(const DiceThrow::Combination& combination); // ActorEnum entfernt bitte beobachten
	void resetRunnerOffsets();
	bool applyRunnerOffsetsToActorMarkersAndCheckWin(const ActorEnum actor);

	struct Column {
		uint8_t actor1Marker;
		uint8_t actor2Marker;
		uint8_t runnerOffset;
	};

private:
	Column m_columns[11];
};
