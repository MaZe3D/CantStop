#pragma once

#include "Board.h"
#include "DiceThrow.h"
#include "ActorEnum.h"

class Actor {
public:
	virtual uint8_t choseCombination(const Board& board, const DiceThrow& diceThrow) = 0;
	virtual bool finishedTurn(const Board& board) = 0;
	virtual void setActorEnum(const ActorEnum actorEnum) final;
	virtual ActorEnum getActorEnum() const final;

private:
	ActorEnum m_actorEnum;
};
