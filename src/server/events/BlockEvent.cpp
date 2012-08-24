#include "BlockEvent.h"

BlockEvent::BlockEvent(EventId eventId, QDataStream& stream) : BaseEvent(eventId, stream), ChunkEvent(eventId, stream)
{
	stream >> m_position;
}

BlockEvent::BlockEvent(EventId eventId, quint32 worldId, const ChunkPosition& chunkPosition, const BlockPosition& blockPosition)
	: BaseEvent(eventId), ChunkEvent(eventId, worldId, chunkPosition), m_position(blockPosition)
{
}

void BlockEvent::serializeTo(QDataStream& stream) const
{
	ChunkEvent::serializeTo(stream);

	stream << m_position;
}

const BlockPosition& BlockEvent::blockPosition() const
{
	return m_position;
}
