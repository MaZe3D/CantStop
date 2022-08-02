#pragma once
#include <memory>
#include "Actor.h"
#include "Board.h"
#include "ActorEnum.h"
#include "util/MersenneTwister.h"
#include <doctest.h>
#include "actors/bots/GreedyBot.h"

class GameRound {
public:
	enum class NextStep {
		CHOOSE_DICE_COMBINATION,
		CHOOSE_TO_CONTINUE_OR_STOP
	};

	GameRound(const std::shared_ptr<Actor>& actor1, const std::shared_ptr<Actor>& actor2, const MersenneTwister& rand);

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

	MersenneTwister m_rand;

	Board m_board;
	std::shared_ptr<Actor> m_actor1;
	std::shared_ptr<Actor> m_actor2;
	DiceThrow m_diceThrow;
};

TEST_CASE("GameRound") {
	MersenneTwister rand = MersenneTwister(0);
	auto actor1 = std::make_shared<GreedyBot>();
	auto actor2 = std::make_shared<GreedyBot>();
	GameRound gameRound(actor1, actor2, rand);
	SUBCASE("First Actor is ACTOR1")
	{
		CHECK(gameRound.getCurrentActorEnum() == ActorEnum::ACTOR1);
	}

	SUBCASE("Next Step is CHOOSE_DICE_COMBINATION")
	{
		CHECK(gameRound.getNextStep() == GameRound::NextStep::CHOOSE_DICE_COMBINATION);
	}

	SUBCASE("Next Step is CHOOSE_TO_CONTINUE_OR_STOP")
	{
		gameRound.nextStep();
		CHECK(gameRound.getNextStep() == GameRound::NextStep::CHOOSE_TO_CONTINUE_OR_STOP);
	}

	SUBCASE("Next Step is CHOOSE_DICE_COMBINATION")
	{
		gameRound.nextStep();
		gameRound.nextStep();
		CHECK(gameRound.getNextStep() == GameRound::NextStep::CHOOSE_DICE_COMBINATION);
	}

	SUBCASE("ACTOR2 is current actor")
	{
		gameRound.nextStep();
		gameRound.nextStep();
		gameRound.nextStep();
		gameRound.nextStep();
		gameRound.nextStep();
		CHECK(gameRound.getCurrentActorEnum() == ActorEnum::ACTOR2);
	}

	SUBCASE("Game is over")
	{
		int i = 0;
		for (i = 0; i < 126; i++) {
			CHECK(gameRound.isOver() == false);
			gameRound.nextStep();
		}
		CHECK(gameRound.isOver() == true);
	}
}