#ifndef MULTIPLAYERTCPSERVER_H
#define MULTIPLAYERTCPSERVER_H

#include <QTcpServer>
#include "MultiplayerServerThread.h"

class MultiplayerServer : public QTcpServer
{
	Q_OBJECT
public:
	explicit MultiplayerServer(QObject *parent = 0);

signals:

public slots:

private:
	void incomingConnection(int handle);

	MultiplayerServerThread m_serverThread;
};

#endif // MULTIPLAYERTCPSERVER_H
