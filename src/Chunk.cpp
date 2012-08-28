#include <cstring> // memcpy
#include <QFutureWatcher>

#include "Chunk.h"
#include "blocks/BlockDescriptor.h"
#include "gui/ChunkDrawer.h"
#include "server/events/ChunkNewDataEvent.h"
#include "server/events/PlayerBlockEvent.h"
#include "server/Server.h"
#include "World.h"

Chunk::Chunk(World* parentWorld, ChunkPosition position)
	: EventReadyObject(parentWorld), m_world(parentWorld), m_state(ChunkState_Idle), b_dirty(true), b_compressed(false), m_position(position)
{
	p_BlockInfos = new BlockInfo[CHUNK_X_SIZE * CHUNK_Z_SIZE * CHUNK_Y_SIZE];

	connect(&fba_compressedChunkWatcher, SIGNAL(finished()), this, SIGNAL(compressed()));
	connect(this, SIGNAL(compressed()), this, SLOT(onCompressed()));
	connect(&fba_uncompressedChunkWatcher, SIGNAL(finished()), this, SIGNAL(uncompressed()));
	connect(this, SIGNAL(uncompressed()), this, SLOT(onUncompressed()));
}

Chunk::~Chunk()
{
	idle();
	delete[] p_BlockInfos;
}

bool Chunk::worldEvent(WorldEvent* worldEvent)
{
	return true;
}

bool Chunk::chunkEvent(ChunkEvent* chunkEvent)
{
	PlayerChunkEvent* playerChunkEvent = dynamic_cast<PlayerChunkEvent*>(chunkEvent);
	if(playerChunkEvent != 0)
	{
		switch(playerChunkEvent->type())
		{
		case Connect_PlayerChunkEventId:
			qDebug() << "Player" << playerChunkEvent->playerId() << "wants the Chunk" << playerChunkEvent->chunkPosition();
			connectPlayer(m_world->player(playerChunkEvent->playerId()));
			m_world->server()->sendNewChunkDataToPlayer(this, playerChunkEvent->playerId());
			return true;
		case Disconnect_PlayerChunkEventId:
			qDebug() << "Player" << playerChunkEvent->playerId() << "doesn't want the Chunk" << playerChunkEvent->chunkPosition();
			disconnectPlayer(playerChunkEvent->playerId());
			return true;
		case ChunkNewDataEventId:
		{
			ChunkNewDataEvent* cndEvent = static_cast<ChunkNewDataEvent*>(playerChunkEvent);
			activate(cndEvent->compressedData());
			return true;
		}
		default:
			return false;
		}
	}

	return true;
}

bool Chunk::blockEvent(BlockEvent* blockEvent)
{
	//qDebug() << "Chunk received BlockEvent ##" << blockEvent->type();

	return true;
}

void Chunk::activate()
{
	QWriteLocker locker(&m_rwLock);
	if(m_state != ChunkState_Active) {
		b_dirty = true; // we must redraw the chunk
		m_state = ChunkState_Active;
		emit activated();
	}
}

void Chunk::activate(const QByteArray& data)
{
	QWriteLocker wLocker(&m_rwLock);
	fba_uncompressedChunk = QtConcurrent::run(qUncompress, data);
	fba_uncompressedChunkWatcher.setFuture(fba_uncompressedChunk);
}

void Chunk::compress()
{
	QWriteLocker wLocker(&m_rwLock);
	b_compressed = false;
	fba_compressedChunk = QtConcurrent::run(qCompress, (uchar*)p_BlockInfos, CHUNK_X_SIZE * CHUNK_Z_SIZE * CHUNK_Y_SIZE * sizeof(BlockInfo), 9);
	fba_compressedChunkWatcher.setFuture(fba_compressedChunk);
}

void Chunk::onCompressed()
{
	QWriteLocker wLocker(&m_rwLock);
	b_compressed = true;

	foreach (quint32 playerId, m_playersWantCompressedChunk) {
		// SEND COMPRESSED CHUNK DATA TO PLAYER
		Player* toPlayer = player(playerId);
		if(toPlayer == NULL) continue;
		qDebug() << "compressed chunk" << m_position << "for player" << playerId;
		ChunkNewDataEvent* event = new ChunkNewDataEvent(ChunkNewDataEventId, m_world->id(), m_position, playerId, fba_compressedChunk.result());
		QCoreApplication::sendEvent(toPlayer, event);
		m_playersWantCompressedChunk.removeAt(m_playersWantCompressedChunk.indexOf(playerId));
	}
}

void Chunk::onUncompressed()
{
	QWriteLocker wLocker(&m_rwLock);
	QByteArray blockInfos = fba_uncompressedChunk.result();
	delete[] p_BlockInfos; // free and reallocate block infos array
	char* blockInfosChar = new char[blockInfos.size()];
	memcpy(blockInfosChar, blockInfos.data(), blockInfos.size());
	p_BlockInfos = reinterpret_cast<BlockInfo*>(blockInfosChar);
	wLocker.unlock();
	activate(); // to quit this function to unlock mutex
}

void Chunk::idle()
{
	QWriteLocker locker(&m_rwLock);
	if(m_state != ChunkState_Idle) {
		m_state = ChunkState_Idle;
		emit idled();
	}
}

int Chunk::altitude(const int x, const int z)
{
	QReadLocker locker(&m_rwLock);
	int highest = 0;
	for(int y = 0; y < CHUNK_HEIGHT; y++)
	{
		if(!block(x, y, z)->descriptor().canPassThrough()) {
			highest = y;
		}
		else { // void
			if(highest != 0) { // If the last block was not void, but this is void, it means that we are on the top
				return highest + 1; // +1 is the size of the cube
			}
		}
	}
	return highest;
}

BlockInfo* Chunk::block(const int x, const int y, const int z)
{
	if(x < 0 || y < 0 || z < 0 || x >= CHUNK_X_SIZE || y >= CHUNK_Y_SIZE || z >= CHUNK_Z_SIZE) {
		return BlockInfo::voidBlock();
	}
	else {
		int ID = y + x * CHUNK_Y_SIZE + z * CHUNK_Y_SIZE * CHUNK_X_SIZE;
		BlockInfo* block = &p_BlockInfos[ID];
		return block;
	}
}

void Chunk::mapToWorld(const int chunkX, const int chunkY, const int chunkZ, int& worldX, int& worldY, int& worldZ) const
{
	worldX = m_position.first * CHUNK_X_SIZE + chunkX;
	worldY = chunkY;
	worldZ = m_position.second * CHUNK_Z_SIZE + chunkZ;
}

void Chunk::makeDirty()
{
	QWriteLocker locker(&m_rwLock);
	b_dirty = true;
	b_compressed = false;
	emit dirtied();
}

void Chunk::makeSurroundingChunksDirty() const
{
	world().chunk(ChunkPosition(m_position.first - 1, m_position.second    ))->makeDirty();
	world().chunk(ChunkPosition(m_position.first + 1, m_position.second    ))->makeDirty();
	world().chunk(ChunkPosition(m_position.first    , m_position.second - 1))->makeDirty();
	world().chunk(ChunkPosition(m_position.first    , m_position.second + 1))->makeDirty();
}

Chunk::ChunkState Chunk::state()
{
	QReadLocker locker(&m_rwLock);
	return m_state;
}

void Chunk::addPlayerWhoWantCompressedChunk(quint32 playerId)
{
	m_playersWantCompressedChunk.append(playerId);
}
