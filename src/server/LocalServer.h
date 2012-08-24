#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include "Server.h"

class LocalServer : public Server
{
	Q_OBJECT
public:
	explicit LocalServer(QObject* parent, int seed);
	virtual ~LocalServer();
};

#endif // LOCALSERVER_H
