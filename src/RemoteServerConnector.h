#ifndef REMOTESERVERCONNECTOR_H
#define REMOTESERVERCONNECTOR_H

#include <QtNetwork/QTcpSocket>

#include "ServerConnector.h"
#include "World.h"

class RemoteServerConnector : public ServerConnector
{
public:
	RemoteServerConnector();

	virtual World& world() { return *m_world; }

private:
	QTcpSocket m_socket;
	World* m_world;
};

#endif // REMOTESERVERCONNECTOR_H
