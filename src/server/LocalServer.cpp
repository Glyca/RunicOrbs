#include "LocalServer.h"
#include "../Log.h"

LocalServer::LocalServer(QObject* parent, int seed) : Server(parent, seed)
{
	ldebug(Channel_Server, "Started local server!");
}

LocalServer::~LocalServer()
{
	delete m_world;
}
