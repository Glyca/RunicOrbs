#include <QTimer>
#include "ClientHandler.h"
#include "Log.h"
#include "MultiplayerServer.h"
#include "ServerConfiguration.h"

const int MAX_CLIENTTHREADS = 4;

MultiplayerServer::MultiplayerServer(ServerConfiguration* serverConfiguration)
	: Server(reinterpret_cast<QObject*>(this), serverConfiguration->getSeed()), m_configuration(serverConfiguration), i_maxClientThreads(MAX_CLIENTTHREADS)
{
	if(listen(QHostAddress::Any, m_configuration->getPort())) {
		linfo(Channel_Server, QObject::tr("Listening to port %1").arg(m_configuration->getPort()));
	}
	else {
		lerror(Channel_Server, QObject::tr("Can't listen to port %1! Isn't the server already launched?").arg(m_configuration->getPort()));
	}

	m_world->enableChunkGeneration(true);

	ldebug(Channel_Server, "Started multiplayer server!");
}

MultiplayerServer::~MultiplayerServer()
{
	delete m_configuration;
	// Quit all threads
	for(uint i = 0; i < m_clientPools.size(); ++i) {
		m_clientPools[i]->thread->quit();
	}
	// Delete all ClientPools
	while(m_clientPools.size()) {
		ClientPool* pool = m_clientPools.back();
		delete pool;
		m_clientPools.pop_back();
	}
}

bool MultiplayerServer::event(QEvent *event)
{
	return Server::event(event);
}

void MultiplayerServer::sendNewChunkDataToPlayer(Chunk* chunk, quint32 playerId)
{
	qDebug() << "compressing chunk" << chunk->position() << "for player" << playerId;
	chunk->addPlayerWhoWantCompressedChunk(playerId);
	chunk->compress();
}

void MultiplayerServer::incomingConnection(int handle)
{
	ldebug(Channel_Server, "Client connecting...");

	ClientHandler* clientHandler = new ClientHandler(handle, this);

	if(m_clientPools.size() < i_maxClientThreads) {
		ldebug(Channel_Server, "Client going in a new thread...");

		ClientPool* newClientPool = new ClientPool();
		QObject::connect(newClientPool->thread, SIGNAL(finished()), newClientPool->thread, SLOT(deleteLater()));
		newClientPool->thread->start();
		m_clientPools.push_back(newClientPool);

		newClientPool->numberOfClients++;
		QObject::connect(newClientPool->thread, SIGNAL(finished()), clientHandler, SLOT(deleteLater()));
		clientHandler->moveToThread(newClientPool->thread);
		QTimer::singleShot(0, clientHandler, SLOT(bind()));
	}
	else {
		int minClients = 9999999;
		// 1 : Find what is the lowest client count among threads
		for(uint i = 0; i < m_clientPools.size(); ++i) {
			if(m_clientPools[i]->numberOfClients < minClients) {
				minClients = m_clientPools[i]->numberOfClients;
			}
		}
		// 2 : and pass our client to this thread
		for(uint i = 0; i < m_clientPools.size(); ++i) {
			if(m_clientPools[i]->numberOfClients == minClients) {
				ldebug(Channel_Server, QString("Client going in thread #%1...").arg(i));

				m_clientPools[i]->numberOfClients++;
				QObject::connect(m_clientPools[i]->thread, SIGNAL(finished()), clientHandler, SLOT(deleteLater()));
				clientHandler->moveToThread(m_clientPools[i]->thread);
				QTimer::singleShot(0, clientHandler, SLOT(bind()));

				return;
			}
		}
	}
}
