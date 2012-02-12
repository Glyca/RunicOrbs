#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include "World.h"

class Server : public QObject
{
	Q_OBJECT
public:
	explicit Server(QObject *parent = 0);

	World& world() { return *m_world; }
	
signals:
	
public slots:

protected:
		World* m_world;
	
};

#endif // SERVER_H
