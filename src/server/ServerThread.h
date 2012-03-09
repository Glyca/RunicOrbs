#ifndef SERVER_H
#define SERVER_H

#include <QThread>

#include "World.h"

class ServerThread : public QThread
{
	Q_OBJECT
public:
	explicit ServerThread(QThread* parent = 0);

	World& world() { return *m_world; }

signals:

public slots:

protected:
		World* m_world;

};

#endif // SERVER_H
