#include "ServerThread.h"
#include "version.h"

ServerThread::ServerThread(QThread *parent) :
	QThread(parent)
{
	qDebug("Starting Craftux server version " CRAFTUX_VERSION " ...");
}
