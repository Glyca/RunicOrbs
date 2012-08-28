#include "ChunkGenerator.h"
#include "Log.h"
#include "server/events/PlayerBlockEvent.h"
#include "PhysicEngine.h"
#include "PhysicObject.h"
#include "server/Server.h"
#include "World.h"

#include <QDebug>

World::World(Server* parentServer, const int seed)
	: EventReadyObject(parentServer), m_server(parentServer), i_worldId(0), b_canGenerateChunks(false), i_time(0), i_seed(seed)
{
	m_physicEngine = new PhysicEngine(this, this);
	m_chunks = new QHash<ChunkPosition, Chunk*>();
	m_voidChunk = new Chunk(this, ChunkPosition(999999,999999));

	ldebug(Channel_Server, tr("Created a world with seed %1 and time %2.").arg(i_seed).arg(i_time));
}

World::~World()
{
	QHashIterator<ChunkPosition, Chunk*> it(*m_chunks);
	while (it.hasNext()) {
		it.next();
		delete it.value(); // Delete each chunks of the world
	}
	delete m_chunks;
	delete m_voidChunk;
	delete m_physicEngine;
}

Server* World::server()
{
	return m_server;
}

int World::id() const
{
	return i_worldId;
}

const PhysicObject* World::po(const int id) const
{
	return m_physicEngine->po(id);
}

int World::nextPhysicObjectId()
{
	return m_server->nextPhysicObjectId();
}

const QHash<ChunkPosition, Chunk*>* World::chunks() const
{
	return m_chunks;
}

Chunk* World::chunk(const ChunkPosition& position) const
{
	if(isChunkLoaded(position)) // If the chunk is already loaded
	{
		return m_chunks->value(position);
	}
	else // otherwise, we return a void chunk (and we DONT load it)
	{
		return m_voidChunk;
	}
}

Chunk* World::chunk(const BlockPosition& position) const
{
	return chunk(chunkPosition(position.x, position.z));
}

ChunkPosition World::chunkPosition(const int x, const int z) const
{
	int cx, cz;
	// without this check, it would return 0;0 for the chunk at -0.5;-0.3
	// but chunk -0;-0 is the same as 0;0, hence the -1 to have chunk -1;-1
	if(x < 0) {
		cx = (x+1) / CHUNK_X_SIZE - 1;
	}
	else {
		cx = x / CHUNK_X_SIZE;
	}
	if(z < 0) {
		cz = (z+1) / CHUNK_Z_SIZE - 1;
	}
	else {
		cz = z / CHUNK_Z_SIZE;
	}
	return ChunkPosition(cx, cz);
}

ChunkPosition World::chunkPosition(const BlockPosition& position) const
{
	return chunkPosition(position.x, position.z);
}

bool World::isChunkLoaded(const ChunkPosition& position) const
{
	return m_chunks->contains(position);
}

void World::enableChunkGeneration(bool yes)
{
	b_canGenerateChunks = yes;
}

void World::loadChunk(const ChunkPosition& position)
{
	if(isChunkLoaded(position)) // safety : If the chunk is already loaded
	{
		return;
	}
	else // otherwise, we generate a new fresh one
	{
		createChunk(position);
	}
}

void World::createChunk(const ChunkPosition& position)
{
	Chunk* newChunk = new Chunk(this, position);
	if(b_canGenerateChunks)
	{
		ChunkGenerator* chunkGenerator = new ChunkGenerator(newChunk, i_seed);
		qDebug() << "generating chunk" << position;
		// The generation thread will auto-destroy itself when finished
		connect(chunkGenerator, SIGNAL(finished()), chunkGenerator, SLOT(deleteLater()));
		// The generation thread will activate the chunk when finished
		connect(chunkGenerator, SIGNAL(finished()), newChunk, SLOT(activate()));
		// Start the generation of the chunk
		chunkGenerator->start();
	}
	m_chunks->insert(position, newChunk);
}

void World::unloadChunk(Chunk* chunk)
{
	unloadChunk(m_chunks->key(chunk));
}

void World::unloadChunk(const ChunkPosition& position)
{
	delete m_chunks->value(position);
	m_chunks->remove(position);
}

BlockInfo* World::block(const BlockPosition& bp) const
{
	ChunkPosition chunkPos = chunkPosition(bp);
	int chunkBlockX, chunkBlockZ; // the coordinates of the block relative to the chunk
	if(bp.x < 0) {
		chunkBlockX = bp.x - chunkPos.first * CHUNK_X_SIZE;
	}
	else { // in positives we can use modulo
		chunkBlockX = bp.x % CHUNK_X_SIZE;
	}

	if(bp.z < 0) {
		chunkBlockZ = bp.z - chunkPos.second * CHUNK_Z_SIZE;
	}
	else {
		chunkBlockZ = bp.z % CHUNK_Z_SIZE;
	}

	return chunk(chunkPos)->block(chunkBlockX, bp.y, chunkBlockZ);
}

BlockInfo* World::block(const Vector& position)
{
	BlockPosition bp = position.toBlock();// Get the block integer coordinates in the world
	return this->block(bp);
}

int World::altitude(const int x, const int z)
{
	ChunkPosition chunkPos = chunkPosition(x, z);
	int chunkBlockX, chunkBlockZ; // the coordinates of the block relative to the chunk

	if(x < 0) {
		chunkBlockX = x - chunkPos.first * CHUNK_X_SIZE;
	}
	else { // in positives we can use modulo
		chunkBlockX = x % CHUNK_X_SIZE;
	}

	if(z < 0) {
		chunkBlockZ = z - chunkPos.second * CHUNK_Z_SIZE;
	}
	else {

		chunkBlockZ = z % CHUNK_Z_SIZE;
	}
	return chunk(chunkPos)->altitude(chunkBlockX, chunkBlockZ);
}

BlockPosition World::highestBlock(const Vector& position)
{
	BlockPosition blockPosition = position.toBlock();
	blockPosition.y = altitude(blockPosition.x, blockPosition.z);
	return blockPosition;
}

bool World::worldEvent(WorldEvent* worldEvent)
{
	// For now do nothing
	//qDebug() << "World received WorldEvent ##" << worldEvent->type();
	return false;
}

bool World::chunkEvent(ChunkEvent* chunkEvent)
{
	//qDebug() << "World received ChunkEvent ##" << chunkEvent->type();

	// Send the event to the concerned chunk
	ChunkPosition chunkPosition = chunkEvent->chunkPosition();
	if(isChunkLoaded(chunkPosition)) {
		return QCoreApplication::sendEvent(chunk(chunkPosition), chunkEvent);
	}
	else
	{
		// The demanded chunk is not loaded !
		loadChunk(chunkPosition);
		return this->chunkEvent(chunkEvent);
	}
}

bool World::blockEvent(BlockEvent* blockEvent)
{
	// Do nothing
	//qDebug() << "World received BlockEvent ##" << blockEvent->type();

	PlayerBlockEvent* playerBlockEvent = dynamic_cast<PlayerBlockEvent*>(blockEvent);
	if(playerBlockEvent != 0)
	{
		Player* thePlayer = player(playerBlockEvent->playerId());
		if(thePlayer == NULL) return false;

		switch(playerBlockEvent->type())
		{
		case Pick_PlayerBlockEventId:
		{
			if(thePlayer->giveOne(block(playerBlockEvent->blockPosition())->id()))
			{
				block(playerBlockEvent->blockPosition())->setId(0);
				// Make the chunk and chunks arround redrawed
				chunk(playerBlockEvent->blockPosition())->makeDirty();
				chunk(playerBlockEvent->blockPosition())->makeSurroundingChunksDirty();
				// For block events, send them to all player connected to this chunk
				// thus when sb mine a block, everyone will be informed
				chunk(playerBlockEvent->blockPosition())->sendEventToPlayers(playerBlockEvent);
			}
		}
			break;
		case Place_PlayerBlockEventId:
		{
			int blockId = thePlayer->inventorySlot(thePlayer->selectedSlot()).id;
			// If there is not already a block here the player has a block of this id in stock
			if(block(playerBlockEvent->blockPosition())->isVoid() && thePlayer->takeOne(blockId))
			{
				block(playerBlockEvent->blockPosition())->setId(blockId);
				chunk(playerBlockEvent->blockPosition())->makeDirty();
				chunk(playerBlockEvent->blockPosition())->sendEventToPlayers(playerBlockEvent);
			}
		}
			break;
		default:
			break;
		}
	}

	return false;
}

