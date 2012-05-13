#include "TcpServer.h"
#include "ClientThread.h"

TcpServer::TcpServer(QObject* parent) : QTcpServer(parent)
{
}

void TcpServer::incomingConnection(int socketDescriptor)
{
	ClientThread* clientThread = new ClientThread(socketDescriptor, this);
	connect(clientThread, SIGNAL(finished()), clientThread, SLOT(deleteLater()));
	clientThread->start();
}
