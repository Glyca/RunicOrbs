#include "MultiplayerServerThread.h"

MultiplayerServerThread::MultiplayerServerThread() : m_tcpServer(new MultiplayerServer(this))
{

}
