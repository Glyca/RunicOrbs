#ifndef MULTIPLAYERSERVER_H
#define MULTIPLAYERSERVER_H

#include "Server.h"
#include "TcpServer.h"

/*! The multiplayer server, running the TCP server TcpServer. */
class MultiplayerServer : public Server
{
public:
	MultiplayerServer();

private:
	TcpServer* m_tcpServer;
};

#endif // MULTIPLAYERSERVER_H
