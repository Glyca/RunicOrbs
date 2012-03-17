#include "World.h"
#include <QDebug>
#include <QtOpenGL>

World::World(const int seed, QObject *parent) : QObject(parent), m_chunkGenerator(ChunkGenerator(seed)), i_seed(seed)
{
	m_physicEngine = new PhysicEngine(this, this);
	m_chunks = new QHash<ChunkPostition, Chunk*>();
}

World::~World()
{
	QHashIterator<ChunkPostition, Chunk*> it(*m_chunks);
	while (it.hasNext()) {
		it.next();
		delete it.value(); // Delete each chunks of the world
	}
	delete m_chunks;
	delete m_physicEngine;
}

Chunk* World::chunk(const ChunkPostition& position)
{
	if(m_chunks->contains(position)) // If the chunk is already loaded
	{
		return m_chunks->value(position);
	}
	else // otherwise, we load it
	{
		return loadChunk(position);
	}
}

Chunk* World::chunk(const BlockPosition& position)
{
	int x, z;
	// without this check, it would return 0;0 for the chunk at -0.5;-0.3
	// but chunk -0;-0 is impossible, hence the -1
	if(position.x < 0)
	{
		x = position.x / CHUNK_X_SIZE - 1;
	}
	else
	{
		x = position.x / CHUNK_X_SIZE;
	}
	if(position.z < 0)
	{
		z = position.z / CHUNK_Z_SIZE - 1;
	}
	else
	{
		z = position.z / CHUNK_Z_SIZE;
	}
	return chunk(ChunkPostition(x, z));
}

Chunk* World::chunk(const Vector& position)
{
	int x, z;
	// without this check, it would return 0;0 for the chunk at -0.5;-0.3
	// but chunk -0;-0 is impossible, hence the -1
	if(position.x < 0)
	{
		x = position.x / CHUNK_X_SIZE - 1;
	}
	else
	{
		x = position.x / CHUNK_X_SIZE;
	}
	if(position.z < 0)
	{
		z = position.z / CHUNK_Z_SIZE - 1;
	}
	else
	{
		z = position.z / CHUNK_Z_SIZE;
	}
	return chunk(ChunkPostition(x, z));
}

Chunk* World::loadChunk(const ChunkPostition& position)
{
	if(m_chunks->contains(position)) // safety : If the chunk is already loaded
	{
		return m_chunks->value(position);
	}
	else // otherwise, we generate a new fresh one
	{
		Chunk* newChunk = new Chunk(this, position);
		m_chunkGenerator.setChunkToGenerate(newChunk);
		m_chunkGenerator.run();
		m_chunks->insert(position, newChunk);
		emit chunkLoaded(position);
		return newChunk;
	}
}

void World::unloadChunk(Chunk* chunk)
{
	unloadChunk(m_chunks->key(chunk));
}

void World::unloadChunk(const ChunkPostition& position)
{
	delete m_chunks->value(position);
	m_chunks->remove(position);
}

BlockInfo* World::block(const BlockPosition& bp)
{
	int chunkBlockX, chunkBlockZ; // the coordinates of the block relative to the chunk

	if(bp.x < 0)
	{
		int chunkPosX = bp.x / CHUNK_X_SIZE - 1;
		chunkBlockX = bp.x - chunkPosX * CHUNK_X_SIZE;
	}
	else // in positives we can use modulo
	{
		chunkBlockX = bp.x % CHUNK_X_SIZE;
	}

	if(bp.z < 0)
	{
		int chunkPosZ = bp.z / CHUNK_Z_SIZE - 1;
		chunkBlockZ = bp.z - chunkPosZ * CHUNK_Z_SIZE;
	}
	else
	{
		chunkBlockZ = bp.z % CHUNK_Z_SIZE;
	}

	return chunk(bp)->block(chunkBlockX, bp.y, chunkBlockZ);
}

BlockInfo* World::block(const Vector& position)
{
	BlockPosition bp = position.toBlock();// Get the block integer coordinates in the world
	return this->block(bp);
}

void World::render3D()
{
	QHash<ChunkPostition, Chunk*>::const_iterator it = m_chunks->constBegin();
	QHash<ChunkPostition, Chunk*>::const_iterator endit = m_chunks->constEnd();
	while (it != endit) {
		it.value()->render3D();
		++it;
	}
}
