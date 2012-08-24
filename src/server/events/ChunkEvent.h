#ifndef CHUNKEVENT_H
#define CHUNKEVENT_H

#include "Chunk.h"
#include "WorldEvent.h"

/*! A WorldEvent that happened in a Chunk
  Compared to the WorldEvent, it contains one more information about the Chunk where the event occurred
*/
class ChunkEvent : public WorldEvent
{
public:
	ChunkEvent(EventId eventId, QDataStream& stream);
	ChunkEvent(EventId eventId, quint32 worldId, const ChunkPosition& chunkPosition);
	virtual ~ChunkEvent();

	virtual void serializeTo(QDataStream& stream) const;

	const ChunkPosition& chunkPosition() const { return m_position; }

private:
	ChunkPosition m_position;
};

#endif // CHUNKEVENT_H
