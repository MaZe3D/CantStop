#pragma once
#include "mysdl/Events.h"
#include "logic/GameRound.h"
#include "drawables/TextureDrawable.h"

class BoardDrawer : WindowResizedEvent {
public:
	BoardDrawer(const std::shared_ptr<Window> window);

	void setGameRound(const std::shared_ptr<GameRound>& round);

	void activate();
	void deactivate();

	void updatePillars();

	void draw();

private:
	struct Column {
		Column(const BoardDrawer&);

		TextureDrawable actor1Pillar;
		TextureDrawable actor2Pillar;
		TextureDrawable runnerPillar;
	};

	const std::shared_ptr<const Texture> m_actor1Texture;
	const std::shared_ptr<const Texture> m_actor2Texture;
	const std::shared_ptr<const Texture> m_runnerTexture;
	Column m_columns[11];

	float m_pillarIncrement;
	std::shared_ptr<GameRound> m_round;

	void onWindowResized(int width, int height) override;
};
