#include "LocalServer.h"
#include "../Log.h"

LocalServer::LocalServer(QObject* parent, int seed) : Server(parent, seed)
{
	m_world->enableChunkGeneration(true);
}

LocalServer::~LocalServer()
{
	delete m_world;
}

void LocalServer::start()
{
	Player* soloPlayer = newPlayer();
	emit playerReady(soloPlayer->id());

	ldebug(Channel_Server, "Started local server!");
}

void LocalServer::sendNewChunkDataToPlayer(Chunk* chunk, quint32 playerId)
{
	Q_UNUSED(chunk); Q_UNUSED(playerId);
}
