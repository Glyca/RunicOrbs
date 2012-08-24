#ifndef PLAYERCHUNKEVENT_H
#define PLAYERCHUNKEVENT_H

#include "ChunkEvent.h"
#include "PlayerEvent.h"

class PlayerChunkEvent : virtual public BaseEvent, public ChunkEvent, public PlayerEvent
{
public:
	PlayerChunkEvent(EventId eventId, QDataStream& stream);
	PlayerChunkEvent(EventId eventId, quint32 worldId, const ChunkPosition& chunkPosition, quint32 playerId);
	virtual ~PlayerChunkEvent();

	virtual void serializeTo(QDataStream& stream) const;
};

#endif // PLAYERCHUNKEVENT_H
