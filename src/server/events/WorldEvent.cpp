#include "WorldEvent.h"

WorldEvent::WorldEvent(EventId eventId, QDataStream& stream) : BaseEvent(eventId, stream)
{
	stream >> i_worldId;
}

WorldEvent::WorldEvent(EventId eventId, quint32 worldId) : BaseEvent(eventId), i_worldId(worldId)
{
}

WorldEvent::~WorldEvent()
{
}

void WorldEvent::serializeTo(QDataStream& stream) const
{
	BaseEvent::serializeTo(stream);

	stream << i_worldId;
}
