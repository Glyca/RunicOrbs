#ifndef WORLD_H
#define WORLD_H

#include <QHash>
#include <QMap>

#include "Chunk.h"
#include "EventReadyObject.h"
#include "Player.h"

class BlockInfo;
class BlockPosition;
class PhysicEngine;
class PhysicObject;
class Server; // avoid circular inclusions
class Vector;

class World : public EventReadyObject
{
public:
	explicit World(Server* parentServer, const int seed);
	~World();

	Server* server();
	int id() const;

	/*! Return the PhysicEngine of the world */
	inline PhysicEngine* physicEngine() const {return m_physicEngine;}
	/*! Return a reference to an entity */
	const PhysicObject* po(const int id) const;

	int nextPhysicObjectId();

	const QHash<ChunkPosition, Chunk*>* chunks() const;

	/*! Access to a chunk of the world from a chunk position */
	Chunk* chunk(const ChunkPosition& position) const;
	/*! Access to a chunk of the world from a block position */
	Chunk* chunk(const BlockPosition& position) const;

	/*! Access to a ChunkPosition of the world from world relative coordinates */
	ChunkPosition chunkPosition(const int x, const int z) const;
	/*! Access to a ChunkPosition of the world from a block position */
	ChunkPosition chunkPosition(const BlockPosition& position) const;

	virtual bool worldEvent(WorldEvent* worldEvent);
	virtual bool chunkEvent(ChunkEvent* chunkEvent);
	virtual bool blockEvent(BlockEvent* blockEvent);

	/*! Return true if the Chunk is loaded, false otherwise */
	bool isChunkLoaded(const ChunkPosition& position) const;

	void enableChunkGeneration(bool yes);

	/*! Load a chunk of the workd into RAM */
	void loadChunk(const ChunkPosition& position);
	/*! Create a chunk
		If b_canGenerateChunks == true it will generate it, otherwise, it will create a void chunk */
	void createChunk(const ChunkPosition& position);
	/*! Free the chunk from the RAM, it will not be rendered anymore */
	void unloadChunk(Chunk* chunk);
	void unloadChunk(const ChunkPosition& position);

	BlockInfo* block(const BlockPosition& position) const;
	BlockInfo* block(const Vector& position);

	int altitude(const int x, const int z);
	/*! Return the highest block coordinates for a given position */
	BlockPosition highestBlock(const Vector& position);

	inline int seed() const {return i_seed;}
	inline void setSeed(const int seed) {i_seed = seed;}

public slots:

private:
	World(){}

	Server* m_server; //!< The Server this World belongs to
	int i_worldId; //!< The Id of the World
	bool b_canGenerateChunks; //!< Whether this World is authorized to generate chunks
	QHash<ChunkPosition, Chunk*> * m_chunks;
	Chunk* m_voidChunk; //!< The void chunk is given when you try to access a too far chunk
	QMap<int, Player*> m_players; //!< Players who are in this world
	PhysicEngine* m_physicEngine;
	int i_time; //!< The current time of the word
	int i_seed; //!< Seed of the world
};

#endif // WORLD_H
