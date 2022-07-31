#pragma once
#include <memory>
#include "Actor.h"
#include "Board.h"
#include "ActorEnum.h"

class GameRound {
public:
	GameRound(const std::shared_ptr<Actor>& actor1, const std::shared_ptr<Actor>& actor2);

	const Board& getBoard();
	ActorEnum getCurrentActor();
	bool isOver();

	void nextStep();

private:
	ActorEnum m_currentActor = ActorEnum::ACTOR1;
	bool m_isOver = false;

	Board m_board;
	std::shared_ptr<Actor> m_actor1;
	std::shared_ptr<Actor> m_actor2;
};
