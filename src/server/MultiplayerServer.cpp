#include "MultiplayerServer.h"

MultiplayerServer::MultiplayerServer(QObject *parent) :
	QTcpServer(parent)
{
}

void MultiplayerServer::incomingConnection(int handle)
{

}
