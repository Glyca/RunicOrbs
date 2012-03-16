#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QAbstractSocket>
#include <QTcpSocket>

/*! Created by a MultiplayerServer to talk with a Client */
class ClientThread : public QThread
{
	Q_OBJECT

public:
	ClientThread(int socketDescriptor, QObject* parent);

	void run();

signals:
	void error(QTcpSocket::SocketError socketError);

private:
	int i_socketDescriptor;
};

#endif // CLIENTTHREAD_H
