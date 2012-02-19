#include <cmath> // floor

#include "World.h"

World::World(QObject *parent) : QObject(parent)
{
	m_physicEngine = new PhysicEngine(this, this);
	m_chunks = new QHash<QPair<int, int>, Chunk*>();
}

World::~World()
{
	QHashIterator<QPair<int, int>, Chunk*> it(*m_chunks);
	while (it.hasNext()) {
		it.next();
		delete it.value(); // Delete each chunks of the world
	}
	delete m_chunks;
}

void World::vector2int(Vector& vector, int& ix, int& iy, int& iz)
{
	ix = floor(vector.x);
	iy = floor(vector.y);
	iz = floor(vector.z);
}

Chunk* World::chunk(QPair<int, int> postion)
{
	if(m_chunks->contains(postion))
	{
		return m_chunks->value(postion);
	}
	else
	{
		Chunk* newChunk = new Chunk(this);
		newChunk->generate(i_seed);
		m_chunks->insert(postion, newChunk);
		return newChunk;
	}
}

Chunk* World::chunk(const Vector& position)
{
	int x = position.x / CHUNK_X_SIZE;
	int z = position.z / CHUNK_Z_SIZE;
	return chunk(QPair<int, int>(x, z));
}

BlockInfo* World::block(const Vector& position)
{
	return chunk(position)->block((int)floor(position.x) % CHUNK_X_SIZE, (int)floor(position.y), (int)floor(position.z) % CHUNK_Z_SIZE); // Very ugly casts !
}
