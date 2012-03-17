#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include "Server.h"

class LocalServer : public Server
{
	Q_OBJECT
public:
	LocalServer(QObject* parent = 0);
};

#endif // LOCALSERVER_H
