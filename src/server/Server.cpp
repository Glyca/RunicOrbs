#include "Server.h"
#include "version.h"

Server::Server(QObject *parent) : QObject(parent)
{
	qDebug("Starting Craftux server version " CRAFTUX_VERSION " ...");
}

void Server::pickBlock(const BlockPosition& blockPosition)
{
	m_world->block(blockPosition)->setId(0);
	m_world->chunk(blockPosition)->makeDirty();
}

void Server::useBlock(const BlockPosition& blockPosition)
{

}
