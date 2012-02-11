#include "Server.h"
#include "version.h"

Server::Server(QObject *parent) :
	QObject(parent)
{
	qDebug("Starting Craftux server version " CRAFTUX_VERSION " ...");
}
