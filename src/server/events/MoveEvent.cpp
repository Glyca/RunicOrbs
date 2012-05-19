#include "MoveEvent.h"
#include "server/Server.h"

MoveEvent::MoveEvent(const Entity::WalkDirection direction, Entity* entity) : m_direction(direction), m_entity(entity)
{
}

void MoveEvent::perform(Server& server) const // TODO : will not work in multiplayer
{
	Q_UNUSED(server);
}

QByteArray MoveEvent::serialize() const
{
	// TODO
	QByteArray byteArray;

	return byteArray;
}
