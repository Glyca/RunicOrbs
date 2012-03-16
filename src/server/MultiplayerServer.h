#ifndef MULTIPLAYERTCPSERVER_H
#define MULTIPLAYERTCPSERVER_H

#include <QTcpServer>

/*! The mulitplayer TCP server, aggregated in a MultiplayerServerThread. It creates a ClientThread for each client.*/
class MultiplayerServer : public QTcpServer
{
	Q_OBJECT
public:
	explicit MultiplayerServer(QObject *parent = 0);

signals:

public slots:

private:
	void incomingConnection(int socketDescriptor);

};

#endif // MULTIPLAYERTCPSERVER_H
