#pragma once

#include "Board.h"
#include "ActorEnum.h"

class DiceThrow {
public:
	struct Combination;

	DiceThrow(const Board& board, const ActorEnum currentActor);
	const uint8_t m_dice[4];
	std::list<const Combination> m_combinations;

	struct Combination {
		const int8_t a;
		const int8_t b;
	};
};
