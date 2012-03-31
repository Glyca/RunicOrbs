#ifndef CHUNKEVENT_H
#define CHUNKEVENT_H

#include "Chunk.h"
#include "ServerEvent.h"

/*! An abstract class for an event of chunk */
class ChunkEvent : public ServerEvent
{
public:
	ChunkEvent(const ChunkPostition& position);

protected:
	ChunkPostition m_chunkPosition;
};

#endif // CHUNKEVENT_H
