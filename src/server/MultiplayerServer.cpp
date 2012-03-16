#include "MultiplayerServer.h"
#include "ClientThread.h"

MultiplayerServer::MultiplayerServer(QObject* parent) : QTcpServer(parent)
{
}

void MultiplayerServer::incomingConnection(int socketDescriptor)
{
	ClientThread* clientThread = new ClientThread(socketDescriptor, this);
	connect(clientThread, SIGNAL(finished()), clientThread, SLOT(deleteLater()));
	clientThread->start();
}
