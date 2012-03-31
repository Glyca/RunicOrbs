#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include "events/ClientEvent.h"
#include "events/ServerEvent.h"
#include "World.h"

class Server : public QObject
{
	Q_OBJECT
public:
	explicit Server(QObject* parent = 0);

	World& world() { return *m_world; }

	/*! Return a const reference to a physic object of the server */
	const PhysicObject* po(const int id) const;

	/*! Return a new "per-server unique" PhysicObject id */
	inline int nextPhysicObjectId() {return ++i_nextPhysicObjectId;}

signals:
	/*! Send an event to a client, such as a remote one. FIXME : The event is not destroyed for the moment */
	void postEvent(const ClientEvent* event);

public slots:
	/*! Perform the event (may be received from the network) on the server */
	void takeEvent(const ServerEvent* event);

protected:
	World* m_world;
private:
	int i_nextPhysicObjectId;
};

#endif // SERVER_H
