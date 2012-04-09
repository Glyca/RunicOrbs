#include "World.h"
#include <QDebug>

World::World(Server* server, const int seed, QObject *parent) : QObject(parent), m_server(server), m_chunkGenerator(ChunkGenerator(seed)), i_seed(seed)
{
	m_physicEngine = new PhysicEngine(this, this);
	m_chunks = new QHash<ChunkPosition, Chunk*>();
}

World::~World()
{
	QHashIterator<ChunkPosition, Chunk*> it(*m_chunks);
	while (it.hasNext()) {
		it.next();
		delete it.value(); // Delete each chunks of the world
	}
	delete m_chunks;
	delete m_physicEngine;
}

const PhysicObject* World::po(const int id) const
{
	return m_physicEngine->po(id);
}

Chunk* World::chunk(const ChunkPosition& position)
{
	if(isChunkLoaded(position)) // If the chunk is already loaded
	{
		return m_chunks->value(position);
	}
	else // otherwise, we load it
	{
		static Chunk voidChunk(this, ChunkPosition(999999,999999));
		return &voidChunk;
	}
}

Chunk* World::chunk(const BlockPosition& position)
{
	return chunk(chunkPosition(position.x, position.z));
}

Chunk* World::chunk(const Vector& position)
{
	return chunk(chunkPosition(position.x, position.z));
}

ChunkPosition World::chunkPosition(const int x, const int z)
{
	int cx, cz;
	// without this check, it would return 0;0 for the chunk at -0.5;-0.3
	// but chunk -0;-0 is the same as 0;0, hence the -1 to have chunk -1;-1
	if(x < 0) {
		cx = x / CHUNK_X_SIZE - 1;
	}
	else {
		cx = x / CHUNK_X_SIZE;
	}
	if(z < 0) {
		cz = z / CHUNK_Z_SIZE - 1;
	}
	else {
		cz = z / CHUNK_Z_SIZE;
	}
	return ChunkPosition(cx, cz);
}

ChunkPosition World::chunkPosition(const BlockPosition& position)
{
	return chunkPosition(position.x, position.z);
}

bool World::isChunkLoaded(const ChunkPosition& position)
{
	return m_chunks->contains(position);
}

void World::loadChunk(const ChunkPosition& position)
{
	if(isChunkLoaded(position)) // safety : If the chunk is already loaded
	{
		return;
	}
	else // otherwise, we generate a new fresh one
	{
		Chunk* newChunk = new Chunk(this, position);
		m_chunkGenerator.setChunkToGenerate(newChunk);
		m_chunkGenerator.run();
		m_chunks->insert(position, newChunk);
		newChunk->activate();
	}
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

BlockInfo* World::block(const BlockPosition& bp)
{
	int chunkBlockX, chunkBlockZ; // the coordinates of the block relative to the chunk

	if(bp.x < 0) {
		int chunkPosX = bp.x / CHUNK_X_SIZE - 1;
		chunkBlockX = bp.x - chunkPosX * CHUNK_X_SIZE;
	}
	else { // in positives we can use modulo
		chunkBlockX = bp.x % CHUNK_X_SIZE;
	}

	if(bp.z < 0) {
		int chunkPosZ = bp.z / CHUNK_Z_SIZE - 1;
		chunkBlockZ = bp.z - chunkPosZ * CHUNK_Z_SIZE;
	}
	else {
		chunkBlockZ = bp.z % CHUNK_Z_SIZE;
	}
	ChunkPosition chunkPos = chunkPosition(bp);
	if(isChunkLoaded(chunkPos)) {
		return chunk(chunkPos)->block(chunkBlockX, bp.y, chunkBlockZ);
	}
	else {
		return BlockInfo::voidBlock();
	}
}

BlockInfo* World::block(const Vector& position)
{
	BlockPosition bp = position.toBlock();// Get the block integer coordinates in the world
	return this->block(bp);
}

int World::altitude(const int x, const int z)
{
	int chunkBlockX, chunkBlockZ; // the coordinates of the block relative to the chunk

	if(x < 0) {
		int chunkPosX = x / CHUNK_X_SIZE - 1;
		chunkBlockX = x - chunkPosX * CHUNK_X_SIZE;
	}
	else { // in positives we can use modulo
		chunkBlockX = x % CHUNK_X_SIZE;
	}

	if(z < 0) {
		int chunkPosZ = z / CHUNK_Z_SIZE - 1;
		chunkBlockZ = z - chunkPosZ * CHUNK_Z_SIZE;
	}
	else {
		chunkBlockZ = z % CHUNK_Z_SIZE;
	}

	return chunk(chunkPosition(x, z))->altitude(chunkBlockX, chunkBlockZ);
}

BlockPosition World::highestBlock(const Vector& position)
{
	BlockPosition blockPosition = position.toBlock();
	blockPosition.y = altitude(blockPosition.x, blockPosition.z);
	return blockPosition;
}

void World::render3D()
{
	QHash<ChunkPosition, Chunk*>::const_iterator it = m_chunks->constBegin();
	QHash<ChunkPosition, Chunk*>::const_iterator endit = m_chunks->constEnd();
	while (it != endit) {
		it.value()->render3D();
		++it;
	}
}
