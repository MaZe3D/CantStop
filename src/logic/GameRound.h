#pragma once
#include <memory>
#include "Actor.h"
#include "Board.h"
#include "ActorEnum.h"

class GameRound {
public:
	enum class NextStep {
		CHOOSE_DICE_COMBINATION,
		CHOOSE_TO_CONTINUE_OR_STOP
	};

	GameRound(const std::shared_ptr<Actor>& actor1, const std::shared_ptr<Actor>& actor2);

	const Board& getBoard() const;
	ActorEnum getCurrentActorEnum() const;
	std::shared_ptr<Actor> getCurrentActor() const;
	std::shared_ptr<Actor> getActor(ActorEnum actor) const;
	const DiceThrow& getDiceThrow() const;
	uint8_t getChosenCombinationID() const;
	bool isOver() const;
	NextStep getNextStep() const;

	void nextStep();

private:
	NextStep m_nextStep = NextStep::CHOOSE_DICE_COMBINATION;
	ActorEnum m_currentActor = ActorEnum::ACTOR1;
	bool m_isOver = false;
	uint8_t m_chosenCombinationID = 0;

	Board m_board;
	std::shared_ptr<Actor> m_actor1;
	std::shared_ptr<Actor> m_actor2;
	DiceThrow m_diceThrow;
};
