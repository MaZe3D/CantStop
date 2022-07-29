#include "Actor.h"

void Actor::setActorEnum(const ActorEnum actorEnum) {
	m_actorEnum = actorEnum;
	return 0;
}

ActorEnum Actor::getActorEnum() const {
	return m_actorEnum;
}