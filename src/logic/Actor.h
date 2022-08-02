#pragma once

#include "Board.h"
#include "DiceThrow.h"
#include "ActorEnum.h"
#include "util/MersenneTwister.h"

class Actor {
public:
	virtual uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow, MersenneTwister& rand) = 0;
	virtual bool finishedTurn(const Board& board, MersenneTwister& rand) = 0;
	virtual void setActorEnum(const ActorEnum actorEnum) final;
	virtual ActorEnum getActorEnum() const final;

private:
	ActorEnum m_actorEnum;
};
