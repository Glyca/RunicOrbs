#include "BlockChangedEvent.h"

BlockChangedEvent::BlockChangedEvent(EventId eventId, QDataStream& stream)
	: BaseEvent(eventId, stream), PlayerBlockEvent(eventId, stream)
{
	stream >> m_blockInfo;
}

BlockChangedEvent::BlockChangedEvent(EventId eventId, quint32 worldId, const ChunkPosition& chunkPosition,
									 quint32 playerId, const BlockPosition& blockPosition, const BlockInfo& blockInfo)
	: BaseEvent(eventId), PlayerBlockEvent(eventId, worldId, chunkPosition, blockPosition, playerId), m_blockInfo(blockInfo)
{
}

BlockChangedEvent::~BlockChangedEvent()
{
}

void BlockChangedEvent::serializeTo(QDataStream& stream) const
{
	BaseEvent::serializeTo(stream);
	PlayerBlockEvent::serializeTo(stream);

	stream << m_blockInfo;
}

