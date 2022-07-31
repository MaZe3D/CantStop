#pragma once

#include "ActorEnum.h"
#include <inttypes.h>
#include <list>
#include <random>

class Board;

class DiceThrow {
public:
	struct Combination {
		int8_t a;
		int8_t b;
	};

	DiceThrow(const Board& board, const ActorEnum currentActor);

	uint8_t getDie(uint8_t dieID) const;
	uint8_t getCombinationCount() const;
	const Combination& getCombination(uint8_t combinationID) const;

private:
	int m_dice[4];
	Combination m_combinations[6];
	uint8_t m_combinationCount = 0;
};
