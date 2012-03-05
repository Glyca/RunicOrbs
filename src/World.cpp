#include <cmath> // floor

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
	int x = position.x / CHUNK_X_SIZE;
	int z = position.z / CHUNK_Z_SIZE;
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
		qDebug() << "Generated a chunk @" << postion;
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
	return chunk(position)->block((int)floor(position.x) % CHUNK_X_SIZE, (int)floor(position.y), (int)floor(position.z) % CHUNK_Z_SIZE); // Very ugly casts !
}

void World::render3D()
{
	QHashIterator<QPair<int, int>, Chunk*> it(*m_chunks);
	while (it.hasNext()) {
		it.next();
		it.value()->render3D();
	}
}
