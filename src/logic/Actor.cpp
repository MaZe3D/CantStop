#include "Actor.h"

ActorEnum Actor::getActorEnum() const {
	return m_actorEnum;
}

void Actor::setActorEnum(const ActorEnum actorEnum) {
	m_actorEnum = actorEnum;
}