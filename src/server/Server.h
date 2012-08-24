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

	virtual bool worldEvent(WorldEvent* worldEvent);
	virtual bool chunkEvent(ChunkEvent* chunkEvent);
	virtual bool blockEvent(BlockEvent* blockEvent);

	/*! Return a new "per-server unique" PhysicObject id */
	int nextPhysicObjectId();

protected:
	World* m_world;
	int i_nextPhysicObjectId;

private:
	Server(){}
};

#endif // SERVER_H
