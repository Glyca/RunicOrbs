#ifndef SERVER_H
#define SERVER_H

#include "EventReadyObject.h"
#include "World.h"

class Server : public EventReadyObject
{
	Q_OBJECT
public:
	explicit Server(QObject* parent, int seed);
	virtual ~Server();

	World* world() { return m_world; }

	/*! Return a const reference to a physic object of the server */
	const PhysicObject* po(const int id) const;

	virtual void start(); //!< Start the server

	virtual bool baseEvent(BaseEvent* baseEvent);
	virtual bool worldEvent(WorldEvent* worldEvent);
	virtual bool chunkEvent(ChunkEvent* chunkEvent);
	virtual bool blockEvent(BlockEvent* blockEvent);

	/*! Creates a player in this Server */
	Player* newPlayer();

	/*! Return a new "per-server unique" PhysicObject id */
	int nextPhysicObjectId();

	virtual void sendNewChunkDataToPlayer(Chunk* chunk, quint32 playerId) = 0;

signals:
	void connected();
	/*! Used by ClientServer and LocalServer to inform that the player is ready */
	void playerReady(int playerId);

protected:
	World* m_world;
	int i_nextPhysicObjectId;

private:
	Server(){}
};

#endif // SERVER_H
