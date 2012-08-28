#ifndef MULTIPLAYERSERVER_H
#define MULTIPLAYERSERVER_H

#include <QTcpServer>
#include <QThread>
#include <vector>
#include "Server.h"

class ServerConfiguration;

/*! A thread where many ClientHandler live */
struct ClientPool {
	ClientPool(QThread* thread = new QThread(), int numberOfClients = 0)
		: thread(thread), numberOfClients(numberOfClients) {}
	QThread* thread; //!< The thred where many ClientHandler are living
	int numberOfClients; //!< The number of clients in this thread
};

/*! The multiplayer server */
class MultiplayerServer : public QTcpServer, public Server
{
public:
	MultiplayerServer(ServerConfiguration* serverConfiguration);
	virtual ~MultiplayerServer();

	virtual bool event(QEvent* event); //!< To redirect all events to Server class

	virtual void sendNewChunkDataToPlayer(Chunk* chunk, quint32 playerId);

protected:
	void incomingConnection(int handle);

private slots:

private:
	ServerConfiguration* m_configuration;
	uint i_maxClientThreads; //!< The maximum number of threads that handle clients
	std::vector<ClientPool*> m_clientPools;
};

#endif // MULTIPLAYERSERVER_H
