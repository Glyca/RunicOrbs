#ifndef MULTIPLAYERTCPSERVER_H
#define MULTIPLAYERTCPSERVER_H

#include <QTcpServer>

/*! The mulitplayer TCP server, aggregated in a MultiplayerServer. It creates a ClientThread for each client.*/
class TcpServer : public QTcpServer
{
	Q_OBJECT
public:
	explicit TcpServer(QObject *parent = 0);

signals:

public slots:

private:
	void incomingConnection(int socketDescriptor);

};

#endif // MULTIPLAYERTCPSERVER_H
