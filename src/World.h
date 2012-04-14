#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QHash>

#include "Chunk.h"
#include "ChunkGenerator.h"

class BlockInfo;
class BlockPosition;
class PhysicEngine;
class PhysicObject;
class Server; // avoid circular inclusions
class Vector;

class World : public QObject
{
public:
	explicit World(Server* server, const int seed, QObject *parent = 0);
	~World();

	/*! Return the server where the world is running */
	inline Server* server() const {return m_server;}
	/*! Return the PhysicEngine of the world */
	inline PhysicEngine* physicEngine() const {return m_physicEngine;}
	/*! Return a reference to an entity */
	const PhysicObject* po(const int id) const;

	/*! Access to a chunk of the world from a chunk position */
	Chunk* chunk(const ChunkPosition& position) const;
	/*! Access to a chunk of the world from a block position */
	Chunk* chunk(const BlockPosition& position) const;

	/*! Access to a ChunkPosition of the world from world relative coordinates */
	ChunkPosition chunkPosition(const int x, const int z) const;
	/*! Access to a ChunkPosition of the world from a block position */
	ChunkPosition chunkPosition(const BlockPosition& position) const;

	/*! Return true if the Chunk is loaded, false otherwise */
	bool isChunkLoaded(const ChunkPosition& position) const;

	/*! Load a chunk in the workd into RAM */
	void loadChunk(const ChunkPosition& position);
	/*! Free the chunk from the RAM, it will not be rendered anymore */
	void unloadChunk(Chunk* chunk);
	void unloadChunk(const ChunkPosition& position);

	BlockInfo* block(const BlockPosition& position) const;
	BlockInfo* block(const Vector& position);

	int altitude(const int x, const int z);
	/*! Return the highest block coordinates for a given position */
	BlockPosition highestBlock(const Vector& position);

	inline void setSeed(const int seed) {i_seed = seed;}

	void render3D();

public slots:

private:
	Server* m_server; //!< The server where the world runs
	QHash<ChunkPosition, Chunk*> * m_chunks;
	Chunk* m_voidChunk; //!< The void chunk is given when you try to access a too far chunk
	PhysicEngine* m_physicEngine;
	ChunkGenerator m_chunkGenerator;
	int i_time; //!< The current time of the word
	int i_seed; //!< Seed of the world
};

#endif // WORLD_H
