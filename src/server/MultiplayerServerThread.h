#ifndef MULTIPLAYERSERVER_H
#define MULTIPLAYERSERVER_H

#include "Server.h"
#include "MultiplayerServer.h"

/*! The thread of a multiplayer server, running the TCP server MultiplayerServer. */
class MultiplayerServerThread : public Server
{
public:
	MultiplayerServerThread();

private:
	MultiplayerServer* m_tcpServer;
};

#endif // MULTIPLAYERSERVER_H
