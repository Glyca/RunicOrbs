#ifndef MULTIPLAYERSERVER_H
#define MULTIPLAYERSERVER_H

#include <QtNetwork/QTcpServer>

#include "Server.h"

class MultiplayerServer : public Server
{
public:
	MultiplayerServer();

private:
	QTcpServer* m_tcpServer;
};

#endif // MULTIPLAYERSERVER_H
