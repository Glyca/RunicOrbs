#include "MultiplayerServer.h"

MultiplayerServer::MultiplayerServer() : m_tcpServer(new TcpServer(this))
{

}
