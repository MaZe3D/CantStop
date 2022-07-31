#pragma once
#include "ActorEnum.h"
#include "DiceThrow.h"
#include <inttypes.h>

class Board {
public:
	struct Column {
		uint8_t actor1Marker;
		uint8_t actor2Marker;
		uint8_t runnerOffset;
		uint8_t maxHeight;
	};

	Board();

	const Column& getColumn(uint8_t column) const;
	void advanceRunnerMarkers(const DiceThrow::Combination& combination);
	void resetRunnerOffsets();
	bool applyRunnerOffsetsToActorMarkersAndCheckWin(const ActorEnum actor);

private:
	Column m_columns[11];
};
