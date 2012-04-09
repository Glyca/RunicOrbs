#ifndef CHUNKEVENT_H
#define CHUNKEVENT_H

#include "Chunk.h"
#include "ServerEvent.h"

/*! An abstract class for an event of chunk */
class ChunkEvent : public ServerEvent
{
public:
	ChunkEvent(const ChunkPosition& position);

protected:
	ChunkPosition m_chunkPosition;
};

#endif // CHUNKEVENT_H
