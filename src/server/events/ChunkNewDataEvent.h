#ifndef CHUNKNEWDATAEVENT_H
#define CHUNKNEWDATAEVENT_H

#include "PlayerChunkEvent.h"

/*! This event contains compressed chunk data sended to the player before sending many singly BlockEvent next. */
class ChunkNewDataEvent : public PlayerChunkEvent
{
public:
	ChunkNewDataEvent(EventId eventId, QDataStream& stream);
	ChunkNewDataEvent(EventId eventId, quint32 worldId, const ChunkPosition& chunkPosition, quint32 playerId, const QByteArray& compressedData);
	virtual ~ChunkNewDataEvent();

	virtual void serializeTo(QDataStream& stream) const;

	const QByteArray& compressedData() const;

private:
	QByteArray ba_compressedData;
};

#endif // CHUNKNEWDATAEVENT_H
