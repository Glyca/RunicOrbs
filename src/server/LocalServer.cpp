#include "LocalServer.h"

LocalServer::LocalServer(QObject* parent) : Server(parent)
{
	//TODO : initialize corectly a world
	m_world = new World(123, this);
}
