#include "DiceThrow.h"

DiceThrow::DiceThrow(const Board &board, const ActorEnum currentActor) {
	// throw dices
	m_dice[0] = random(1, 7);
	m_dice[1] = random(1, 7);
	m_dice[2] = random(1, 7);
	m_dice[3] = random(1, 7);

	uint8_t maxValue = m_dice[0] + m_dice[1] + m_dice[2] + m_dice[3];

	// calculate all possible valid combinations for player
	for (int i = 0; i < 3; ++i) {
		for (int j = i+1; j < 4; ++j) {
			Combination combination = {-1, -1};
			uint8_t a = m_dice[i] + m_dice[j];
			uint8_t b = maxValue - a;
			uint8_t& actorMarkera = (currentActor == ActorEnum::Actor1) ? Board::getColumn(a-2).actor1Marker : Board::getColumn(a-2).actor2Marker;
			uint8_t& actorMarkerb = (currentActor == ActorEnum::Actor1) ? Board::getColumn(b-2).actor1Marker : Board::getColumn(b-2).actor2Marker;
			if (actorMarkera + Board::getColumn(a-2).runnerOffset < Board::getColumnHeight(a-2)) {
				combination.a = a;
			}
			if (actorMarkerb + Board::getColumn(b-2).runnerOffset < Board::getColumnHeight(b-2)) {
				combination.b = b;
			}
			m_combinations.push_back(combination);
		}
	}

}