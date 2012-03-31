#include "Server.h"
#include "version.h"

Server::Server(QObject *parent) : QObject(parent), i_nextPhysicObjectId(10)
{
	qDebug("Starting Craftux server version " CRAFTUX_VERSION " ...");
}

void Server::takeEvent(const Event* event)
{
	event->perform(*this);
}
