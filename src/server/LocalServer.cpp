#include "LocalServer.h"

LocalServer::LocalServer(QObject* parent) : Server(parent)
{
	//TODO : initialize corectly a world
	m_world = new World(this, 123, this);
}

LocalServer::~LocalServer()
{
	delete m_world;
}
