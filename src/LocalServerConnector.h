#ifndef LOCALSERVERCONNECTOR_H
#define LOCALSERVERCONNECTOR_H

#include "LocalServer.h"
#include "ServerConnector.h"

class LocalServerConnector : public ServerConnector
{
	Q_OBJECT
public:
	LocalServerConnector();

	virtual World& world() { return m_server.world(); }

private:
	LocalServer m_server;
};

#endif // LOCALSERVERCONNECTOR_H
