#include "PlayerBlockEvent.h"

PlayerBlockEvent::PlayerBlockEvent(EventId eventId, QDataStream& stream)
	: BaseEvent(eventId, stream), PlayerChunkEvent(eventId, stream), BlockEvent(eventId, stream)
{
}

PlayerBlockEvent::PlayerBlockEvent(EventId eventId, quint32 worldId, const ChunkPosition& chunkPosition,
								   const BlockPosition& blockPosition, quint32 playerId)
	: BaseEvent(eventId), PlayerChunkEvent(eventId, worldId, chunkPosition, playerId),
	  BlockEvent(eventId, worldId, chunkPosition, blockPosition)
{

}

PlayerBlockEvent::~PlayerBlockEvent()
{
}

void PlayerBlockEvent::serializeTo(QDataStream& stream) const
{
	BaseEvent::serializeTo(stream);
	PlayerChunkEvent::serializeTo(stream);
	BlockEvent::serializeTo(stream);
}
