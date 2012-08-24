#ifndef BLOCKEVENT_H
#define BLOCKEVENT_H

#include "blocks/BlockInfo.h"
#include "ChunkEvent.h"

class BlockEvent : public ChunkEvent
{
public:
	BlockEvent(EventId eventId, QDataStream& stream);
	BlockEvent(EventId eventId, quint32 worldId, const ChunkPosition& chunkPosition, const BlockPosition& blockPosition);

	virtual void serializeTo(QDataStream& stream) const;

	const BlockPosition& blockPosition() const;

private:
	BlockPosition m_position;
};

#endif // BLOCKEVENT_H
