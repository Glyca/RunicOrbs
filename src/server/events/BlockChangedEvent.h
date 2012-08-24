#ifndef BLOCKCHANGEDEVENT_H
#define BLOCKCHANGEDEVENT_H

#include "PlayerBlockEvent.h"

/*! Event fired when a block has changed (because of a Player).
  Compared to the PlayerBlockEvent it contains one more information about the new block.
  */
class BlockChangedEvent : public PlayerBlockEvent
{
public:
	BlockChangedEvent(EventId eventId, QDataStream& stream);
	BlockChangedEvent(EventId eventId, quint32 worldId, const ChunkPosition& chunkPosition,
					  quint32 playerId, const BlockPosition& blockPosition, const BlockInfo& blockInfo);
	virtual ~BlockChangedEvent();

	virtual void serializeTo(QDataStream& stream) const;

private:
	BlockInfo m_blockInfo;
};

#endif // BLOCKCHANGEDEVENT_H
