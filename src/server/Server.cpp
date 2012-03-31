#include "Server.h"
#include "version.h"

Server::Server(QObject *parent) : QObject(parent), i_nextPhysicObjectId(10)
{
	qDebug("Starting Craftux server version " CRAFTUX_VERSION " ...");
}

const PhysicObject* Server::po(const int id) const
{
	return m_world->po(id);
}

void Server::takeEvent(const ServerEvent* event)
{
	event->perform(*this);
}
