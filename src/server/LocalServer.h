#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include "Server.h"

class LocalServer : public Server
{
	Q_OBJECT
public:
	explicit LocalServer(QObject* parent, int seed);
	virtual ~LocalServer();

	virtual void start();

	/*! For the LocalServer do nothing since we have already all the data */
	virtual void sendNewChunkDataToPlayer(Chunk* chunk, quint32 playerId);
};

#endif // LOCALSERVER_H
