#include <stdexcept>
#include "DiceThrow.h"
#include "Board.h"

DiceThrow::DiceThrow(const Board& board, const ActorEnum currentActor) {

	uint8_t usedRunnerCount = 0;
	uint8_t usedRunners[3];
	for (int i = 0; i < 11; i++) {
		if (board.getColumn(i).runnerOffset > 0)
			usedRunners[usedRunnerCount++] = i+2;
	}

	// throw dice
	for (uint8_t i = 0; i < 4; i++)
		m_dice[i] = rand() % 6 + 1;



	// calculate all possible valid combinations for player
	uint8_t totalDiceSum = m_dice[0] + m_dice[1] + m_dice[2] + m_dice[3];
	for (int i = 1; i < 4; ++i) {
		int8_t a = m_dice[0] + m_dice[i];
		int8_t b = totalDiceSum - a;
		const Board::Column& columnA = board.getColumn(a-2);
		const Board::Column& columnB = board.getColumn(b-2);
		const uint8_t& actorMarkerA            = (currentActor == ActorEnum::ACTOR1) ? columnA.actor1Marker : columnA.actor2Marker;
		const uint8_t& actorMarkerAOtherPlayer = (currentActor == ActorEnum::ACTOR1) ? columnA.actor2Marker : columnA.actor1Marker;
		const uint8_t& actorMarkerB            = (currentActor == ActorEnum::ACTOR1) ? columnB.actor1Marker : columnB.actor2Marker;
		const uint8_t& actorMarkerBOtherPlayer = (currentActor == ActorEnum::ACTOR1) ? columnB.actor2Marker : columnB.actor1Marker;
		if ((actorMarkerAOtherPlayer == columnA.maxHeight) || (actorMarkerA + columnA.runnerOffset >= columnA.maxHeight)) {
			a = -1;
		}
		if ((actorMarkerBOtherPlayer == columnB.maxHeight) || (actorMarkerB + columnB.runnerOffset >= columnB.maxHeight)) {
			b = -1;
		}
		if ((a == b) && (actorMarkerA + columnA.runnerOffset +1 >= columnA.maxHeight)) {
			b = -1;
		}

		if (usedRunnerCount == 3) {
			if (a != usedRunners[0] && a != usedRunners[1] && a != usedRunners[2]) {
				a = -1;
			}
			if (b != usedRunners[0] && b != usedRunners[1] && b != usedRunners[2]) {
				b = -1;
			}
		}
		else if (usedRunnerCount == 2 && a != usedRunners[0] && a != usedRunners[1] && b != usedRunners[0] && b != usedRunners[1]) {
			if (a > 0) insertCombination(a, -1);
			if (b > 0) insertCombination(b, -1);
			continue;
		}

		if (a < 0) {
			a = b;
			b = -1;
		}
		if (a < 0) continue;

		insertCombination(a, b);
	}
	/*if (m_combinationCount > 0)
	while(m_combinationCount < 6) {
		m_combinations[m_combinationCount++] = m_combinations[0];
	}*/
}

void DiceThrow::insertCombination(int8_t a, int8_t b) {
	for (uint8_t i = 0; i < m_combinationCount; i++) {
		if (m_combinations[i].a == a && m_combinations[i].b == b) return;
		if (m_combinations[i].a == b && m_combinations[i].b == a) return;
	}
	m_combinations[m_combinationCount++] = {a, b};
}

uint8_t DiceThrow::getDie(uint8_t dieID) const {
	if (dieID >= 4) throw std::runtime_error("DiceThrow::getDie() - dieID must be smaller than 4");
	return m_dice[dieID];
}

uint8_t DiceThrow::getCombinationCount() const {
	return m_combinationCount;
}

const DiceThrow::Combination& DiceThrow::getCombination(uint8_t combinationID) const {
	if (combinationID >= m_combinationCount) throw std::runtime_error("DiceThrow::getCombination() - invalid combinationID");
	return m_combinations[combinationID];
}
