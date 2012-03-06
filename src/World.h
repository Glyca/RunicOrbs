#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QHash>
#include <QPair>

#include "BlockInfo.h"
#include "Chunk.h"
#include "Entity.h"
#include "PhysicEngine.h"
#include "Vector.h"

typedef QPair<int, int> ChunkPostition;

class World : public QObject
{
	Q_OBJECT
public:
	explicit World(QObject *parent = 0);
	~World();

	inline PhysicEngine* physicEngine() const {return m_physicEngine;}

	/*! Access to a chunk of the world */
	Chunk* chunk(ChunkPostition postion);
	Chunk* chunk(const Vector& postion);

	/*! Load a chunk in the workd into RAM */
	Chunk* loadChunk(ChunkPostition postion);
	/*! Free the chunk from the RAM, it will not be rendered anymore */
	void unloadChunk(Chunk* chunk);
	void unloadChunk(ChunkPostition postion);

	BlockInfo* block(const Vector& position);

	inline void setSeed(const int seed) {i_seed = seed;}

	void render3D();

signals:
	/*! When a chunk has been loaded */
	void chunkLoaded(ChunkPostition postion);

public slots:

private:
	QHash<ChunkPostition, Chunk*> * m_chunks;
	QList<Entity> m_entities;
	PhysicEngine* m_physicEngine;
	int i_time;
	int i_seed; //! Seed of the world
};

#endif // WORLD_H
