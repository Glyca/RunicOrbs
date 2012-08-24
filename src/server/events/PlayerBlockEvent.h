#ifndef PLAYERBLOCKEVENT_H
#define PLAYERBLOCKEVENT_H

#include "BlockEvent.h"
#include "PlayerChunkEvent.h"

class PlayerBlockEvent : public PlayerChunkEvent, public BlockEvent
{
public:
	PlayerBlockEvent(EventId eventId, QDataStream& stream);
	PlayerBlockEvent(EventId eventId, quint32 worldId, const ChunkPosition& chunkPosition, const BlockPosition& blockPosition, quint32 playerId);
	virtual ~PlayerBlockEvent();

	virtual void serializeTo(QDataStream& stream) const;
};

#endif // PLAYERBLOCKEVENT_H
