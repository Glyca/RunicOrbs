#ifndef LOCALSERVERCONNECTOR_H
#define LOCALSERVERCONNECTOR_H

#include "server/LocalServer.h"
#include "ServerConnector.h"

class LocalServerConnector : public ServerConnector
{
	Q_OBJECT
public:
	LocalServerConnector();

	virtual World& world() { return m_server->world(); }

signals:

public slots:
	/*! Each time a chunk gets loaded, we check if we have to load other ones */
	void onChunkLoaded(ChunkPostition position);

private:
	LocalServer* m_server;
};

#endif // LOCALSERVERCONNECTOR_H
