#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <QObject>

#include "server/events/Event.h"
#include "Me.h"
#include "World.h"

class ServerConnector : public QObject
{
	Q_OBJECT
public:
	explicit ServerConnector(QObject *parent = 0);

	virtual World& world();

	inline Me* me() const {return m_me;}

	void pickBlock();
	void useBlock();

signals:
	/*! Send an event to the server. FIXME : The event is not destroyed for the moment */
	void postEvent(const Event* event);

public slots:

protected:
	Me* m_me;
};

#endif // SERVERCONNECTOR_H
