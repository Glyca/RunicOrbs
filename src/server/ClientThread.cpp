#include "ClientThread.h"

ClientThread::ClientThread(int socketDescriptor, QObject* parent) : QThread(parent), i_socketDescriptor(socketDescriptor)
{
}

void ClientThread::run()
{
	QTcpSocket tcpSocket;

	if (!tcpSocket.setSocketDescriptor(i_socketDescriptor))
	{
		emit error(tcpSocket.error());
		return;
	}

	// For the moment we disconnect the client :)
	tcpSocket.disconnectFromHost();
	tcpSocket.waitForDisconnected();
}
