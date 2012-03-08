#include "LocalServer.h"

LocalServer::LocalServer()
{
	//TODO : initialize corectly a world
	m_world = new World(123, this);
}
