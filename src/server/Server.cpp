#include "Log.h"
#include "Server.h"
#include "version.h"

Server::Server(QObject *parent) : QObject(parent), i_nextPhysicObjectId(10)
{
	linfo(Channel_Server, "Starting TRO server version " TRO_VERSION " ...");
}

Server::~Server()
{
	linfo(Channel_Server, "Server is shutting down...");
}

const PhysicObject* Server::po(const int id) const
{
	return m_world->po(id);
}

void Server::takeEvent(const ServerEvent* event)
{
	event->perform(*this);
}
