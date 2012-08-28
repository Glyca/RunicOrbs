#include "ChunkNewDataEvent.h"

ChunkNewDataEvent::ChunkNewDataEvent(EventId eventId, QDataStream& stream)
	: BaseEvent(eventId, stream), PlayerChunkEvent(eventId, stream)
{
	quint32 size;
	stream >> size;
	QByteArray newByteArray(size, Qt::Uninitialized);
	stream.readRawData(newByteArray.data(), size);
	ba_compressedData = newByteArray;
}

ChunkNewDataEvent::ChunkNewDataEvent(EventId eventId, quint32 worldId, const ChunkPosition& chunkPosition, quint32 playerId, const QByteArray& compressedData)
	: BaseEvent(eventId), PlayerChunkEvent(eventId, worldId, chunkPosition, playerId), ba_compressedData(compressedData)
{
}

ChunkNewDataEvent::~ChunkNewDataEvent()
{
}

void ChunkNewDataEvent::serializeTo(QDataStream& stream) const
{
	PlayerChunkEvent::serializeTo(stream);

	stream << (quint32)ba_compressedData.size();
	stream.writeRawData(ba_compressedData.data(), ba_compressedData.size());
}

const QByteArray& ChunkNewDataEvent::compressedData() const
{
	return ba_compressedData;
}
