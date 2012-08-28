#include <QDebug>

#include "server/events/BlockEvent.h"
#include "Log.h"
#include "server/events/PlayerEvent.h"
#include "Server.h"
#include "version.h"

Server::Server(QObject* parent, int seed)
	: EventReadyObject(parent), m_world(NULL), i_nextPhysicObjectId(10)
{
	linfo(Channel_Server, "Starting TRO server version " TRO_VERSION " ...");
	m_world = new World(this, seed);
}

Server::~Server()
{
	linfo(Channel_Server, "Server is shutting down...");
}

const PhysicObject* Server::po(const int id) const
{
	return m_world->po(id);
}

void Server::start()
{

}

bool Server::baseEvent(BaseEvent* baseEvent)
{
	PlayerEvent* playerEvent = dynamic_cast<PlayerEvent*>(baseEvent); // Send player events to their recipients
	if(playerEvent != 0) {
		Player* recipient = player(playerEvent->playerId());
		if(recipient != NULL) {
			return QCoreApplication::sendEvent(recipient, playerEvent);
		}
	}

	return false;
}

bool Server::worldEvent(WorldEvent* worldEvent)
{
	// For now there is just one world, therefore we send all events to it
	//qDebug() << "Server received WorldEvent ##" << worldEvent->type();
	return QCoreApplication::sendEvent(world(), worldEvent);
}

bool Server::chunkEvent(ChunkEvent* chunkEvent)
{
	// For now there is just one world, therefore we send all events to it
	//qDebug() << "Server received ChunkEvent ##" << chunkEvent->type();
	return false;
}

bool Server::blockEvent(BlockEvent* blockEvent)
{
	// For now there is just one world, therefore we send all events to it
	//qDebug() << "Server received BlockEvent ##" << blockEvent->type();
	return false;
}

Player* Server::newPlayer()
{
	Player* newPlayer = new Player(m_world->physicEngine(), nextPhysicObjectId());
	connectPlayer(newPlayer);
	m_world->connectPlayer(newPlayer);
	ldebug(Channel_Server, tr("A new Player #%1 is in the server.").arg(newPlayer->id()));
	return newPlayer;
}

int Server::nextPhysicObjectId()
{
	return ++i_nextPhysicObjectId;
}
