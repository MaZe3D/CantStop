#include "DiceThrow.h"
#include "Board.h"

DiceThrow::DiceThrow(const Board &board, const ActorEnum currentActor) :
	m_dice{ rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1 } {
	// throw dices
	/*m_dice[0] = rand() % 6 + 1;
	m_dice[1] = rand() % 6 + 1;
	m_dice[2] = rand() % 6 + 1;
	m_dice[3] = rand() % 6 + 1;*/

	uint8_t maxValue = m_dice[0] + m_dice[1] + m_dice[2] + m_dice[3];

	// calculate all possible valid combinations for player
	for (int i = 0; i < 3; ++i) {
		for (int j = i+1; j < 4; ++j) {
			int8_t a1, b1;
			uint8_t a = m_dice[i] + m_dice[j];
			uint8_t b = maxValue - a;
			const uint8_t& actorMarkera = (currentActor == ActorEnum::ACTOR1) ? board.getColumn(a-2).actor1Marker : board.getColumn(a-2).actor2Marker;
			const uint8_t& actorMarkerb = (currentActor == ActorEnum::ACTOR1) ? board.getColumn(b-2).actor1Marker : board.getColumn(b-2).actor2Marker;
			if (actorMarkera + board.getColumn(a-2).runnerOffset < board.getColumnHeight(a-2)) {
				a1 = a;
			}
			if (actorMarkerb + board.getColumn(b-2).runnerOffset < board.getColumnHeight(b-2)) {
				b1 = b;
			}
			Combination combination = { a1, b1 };
			m_combinations.push_back(combination);
		}
	}

}