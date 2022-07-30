#pragma once

#include "ActorEnum.h"
#include <inttypes.h>
#include <list>
#include <random>

class Board;

class DiceThrow {
public:
	struct Combination;

	DiceThrow(const Board& board, const ActorEnum currentActor);
	const int m_dice[4];
	std::list<Combination> m_combinations; // unänderbar machen

	struct Combination {
		const int8_t a;
		const int8_t b;
	};
};
