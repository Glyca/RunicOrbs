#include "World.h"
#include <QDebug>
#include <QtOpenGL>

World::World(QObject *parent) : QObject(parent)
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

Chunk* World::chunk(ChunkPostition postion)
{
	if(m_chunks->contains(postion)) // If the chunk is already loaded
	{
		return m_chunks->value(postion);
	}
	else // otherwise, we load it
	{
		return loadChunk(postion);
	}
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

Chunk* World::loadChunk(ChunkPostition postion)
{
	if(m_chunks->contains(postion)) // safety : If the chunk is already loaded
	{
		return m_chunks->value(postion);
	}
	else // otherwise, we generate a new fresh one
	{
		Chunk* newChunk = new Chunk(this, postion);
		newChunk->generate(i_seed);
		m_chunks->insert(postion, newChunk);
		emit chunkLoaded(postion);
		return newChunk;
	}
}

void World::unloadChunk(Chunk* chunk)
{
	unloadChunk(m_chunks->key(chunk));
}

void World::unloadChunk(ChunkPostition postion)
{
	delete m_chunks->value(postion);
	m_chunks->remove(postion);
}

BlockInfo* World::block(const Vector& position)
{
	int x, y, z;
	position.toBlock(x, y, z); // Get the block integer coordinates in the world
	int chunkBlockX, chunkBlockZ; // the coordinates of the block relative to the chunk

	if(x < 0)
	{
		int chunkPosX = x / CHUNK_X_SIZE - 1;
		chunkBlockX = x - chunkPosX * CHUNK_X_SIZE;
	}
	else // in positives we can use modulo
	{
		chunkBlockX = x % CHUNK_X_SIZE;
	}

	if(z < 0)
	{
		int chunkPosZ = z / CHUNK_Z_SIZE - 1;
		chunkBlockZ = z - chunkPosZ * CHUNK_Z_SIZE;
	}
	else
	{
		chunkBlockZ = z % CHUNK_Z_SIZE;
	}

	return chunk(position)->block(chunkBlockX, y, chunkBlockZ);
}

void World::render3D()
{
	QHashIterator<QPair<int, int>, Chunk*> it(*m_chunks);
	while (it.hasNext()) {
		it.next();
		it.value()->render3D();
	}
}
