#include "ChunkEvent.h"

ChunkEvent::ChunkEvent(EventId eventId, QDataStream& stream) : BaseEvent(eventId, stream), WorldEvent(eventId, stream)
{
	stream >> m_position;
}

ChunkEvent::ChunkEvent(EventId eventId, quint32 worldId, const ChunkPosition& chunkPosition)
	: BaseEvent(eventId), WorldEvent(eventId, worldId), m_position(chunkPosition)
{
}

ChunkEvent::~ChunkEvent()
{
}

void ChunkEvent::serializeTo(QDataStream& stream) const
{
	WorldEvent::serializeTo(stream);

	stream << m_position;
}
