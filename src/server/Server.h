#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include "events/Event.h"
#include "World.h"

class Server : public QObject
{
	Q_OBJECT
public:
	explicit Server(QObject* parent = 0);

	World& world() { return *m_world; }

	/*! Return a new "per-server unique" PhysicObject id */
	inline int nextPhysicObjectId() {return ++i_nextPhysicObjectId;}

signals:

public slots:
	void takeEvent(const Event* event);

protected:
	World* m_world;
private:
	int i_nextPhysicObjectId;
};

#endif // SERVER_H
