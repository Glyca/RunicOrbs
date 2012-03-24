#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QHash>

#include "blocks/BlockInfo.h"
#include "Chunk.h"
#include "ChunkGenerator.h"
#include "Entity.h"
#include "PhysicEngine.h"
#include "server/Server.h"
#include "Vector.h"

class World : public QObject
{
	Q_OBJECT
public:
	explicit World(Server* server, const int seed, QObject *parent = 0);
	~World();

	/*! Return the server where the world is running */
	inline Server* server() const {return m_server;}
	inline PhysicEngine* physicEngine() const {return m_physicEngine;}

	/*! Access to a chunk of the world from world relative coordinates */
	Chunk* chunk(const int x, const int z);
	/*! Access to a chunk of the world from a chunk position */
	Chunk* chunk(const ChunkPostition& position);
	/*! Access to a chunk of the world from a block position */
	Chunk* chunk(const BlockPosition& position);
	/*! Access to a chunk of the world from a vector position */
	Chunk* chunk(const Vector& position);

	/*! Load a chunk in the workd into RAM */
	Chunk* loadChunk(const ChunkPostition& position);
	/*! Free the chunk from the RAM, it will not be rendered anymore */
	void unloadChunk(Chunk* chunk);
	void unloadChunk(const ChunkPostition& position);

	BlockInfo* block(const BlockPosition& position);
	BlockInfo* block(const Vector& position);

	int altitude(const int x, const int z);
	/*! Return the highest block coordinates for a given position */
	BlockPosition highestBlock(const Vector& position);

	inline void setSeed(const int seed) {i_seed = seed;}

	void render3D();

signals:
	/*! When a chunk has been loaded */
	void chunkLoaded(ChunkPostition postion);

public slots:

private:
	Server* m_server; //! The server where the world runs
	QHash<ChunkPostition, Chunk*> * m_chunks;
	QList<Entity> m_entities;
	PhysicEngine* m_physicEngine;
	ChunkGenerator m_chunkGenerator;
	int i_time;
	int i_seed; //! Seed of the world
};

#endif // WORLD_H
