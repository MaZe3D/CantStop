#include "BoardDrawer.h"

BoardDrawer::Column::Column(const BoardDrawer& b)
	: actor1Pillar(b.m_actor1Texture)
	, actor2Pillar(b.m_actor2Texture)
	, runnerPillar(b.m_runnerTexture)
{}

BoardDrawer::BoardDrawer(const std::shared_ptr<Window> window)
	: Event(window)
	, m_actor1Texture(window->loadTexture("res/sprites/Game_Player1_Bar.png"))
	, m_actor2Texture(window->loadTexture("res/sprites/Game_Player2_Bar.png"))
	, m_runnerTexture(window->loadTexture("res/sprites/Game_Temp_Bar.png"))
	, m_columns {
		Column(*this), Column(*this), Column(*this), Column(*this), Column(*this), Column(*this),
		Column(*this), Column(*this), Column(*this), Column(*this), Column(*this)
	}
{
	for (Column& c : m_columns) {
		c.actor1Pillar.rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::BOTTOM);
		c.actor2Pillar.rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::BOTTOM);
		c.runnerPillar.rect.setAnchorModeX(Rect::AnchorMode::CENTER).setAnchorModeY(Rect::AnchorMode::BOTTOM);
	}
}

void BoardDrawer::setGameRound(const std::shared_ptr<GameRound>& round) {
	m_round = round;
	onWindowResized(m_window->getWidth(), m_window->getHeight());
	activate();
}

void BoardDrawer::activate() {
	WindowResizedEvent::subscribe();
}

void BoardDrawer::deactivate() {
	WindowResizedEvent::unsubscribe();
}

void BoardDrawer::updatePillars() {
	for (uint8_t i = 0; i < 11; i++) {
		Column& drawColumn = m_columns[i];
		const Board::Column& boardColumn = m_round->getBoard().getColumn(i);
		drawColumn.actor1Pillar.rect.setHeight(boardColumn.actor1Marker * m_pillarIncrement);
		drawColumn.actor2Pillar.rect.setHeight(boardColumn.actor2Marker * m_pillarIncrement);
		Rect& currentActorPillarRect = (m_round->getCurrentActorEnum() == ActorEnum::ACTOR1) ? drawColumn.actor1Pillar.rect : drawColumn.actor2Pillar.rect;
		drawColumn.runnerPillar.rect.setPos(currentActorPillarRect.getPosX(), currentActorPillarRect.getTop());
		drawColumn.runnerPillar.rect.setHeight(boardColumn.runnerOffset * m_pillarIncrement);

		bool actor1Won = (boardColumn.maxHeight == boardColumn.actor1Marker);
		bool actor2Won = (boardColumn.maxHeight == boardColumn.actor2Marker);
		if (actor1Won || actor2Won) {
			Rect& wonPillarRect   = actor1Won ? drawColumn.actor1Pillar.rect : drawColumn.actor2Pillar.rect;
			Rect& otherPillarRect = actor1Won ? drawColumn.actor2Pillar.rect : drawColumn.actor1Pillar.rect;
			wonPillarRect.setWidth(drawColumn.runnerPillar.rect.getWidth()*2);
			otherPillarRect.setWidth(drawColumn.runnerPillar.rect.getWidth()/2);
		}
	}
}

void BoardDrawer::draw() {
	for(const Column& c : m_columns) {
		c.actor1Pillar.draw();
		c.actor2Pillar.draw();
		c.runnerPillar.draw();
	}
}

void BoardDrawer::onWindowResized(int width, int height) {
	const float firstPillarPosX    = - height * ( 786.5/2160) + (width/2.);
	const float firstPillarPosY    =   height * (1657.0/2160);
	const float pillarSpacing      =   height * ( 152.6/2160);
	const float pillarPairDistance =   height * (  47.0/2160);
	const float pillarWidth = height/20.;
	m_pillarIncrement = height*7/135.;

	for (uint8_t i = 0; i < 11; i++) {
		Column& c = m_columns[i];
		c.actor1Pillar.rect.setPos(firstPillarPosX + (i * pillarSpacing)                     , firstPillarPosY);
		c.actor2Pillar.rect.setPos(firstPillarPosX + (i * pillarSpacing) + pillarPairDistance, firstPillarPosY);
		c.runnerPillar.rect.setPos(firstPillarPosX + (i * pillarSpacing) + pillarPairDistance, firstPillarPosY);

		c.actor1Pillar.rect.setWidth(pillarWidth);
		c.actor2Pillar.rect.setWidth(pillarWidth);
		c.runnerPillar.rect.setWidth(pillarWidth);
	}

	updatePillars();
}
