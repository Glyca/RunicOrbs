#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <QObject>
#include <QList>

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

	void setViewDistance(const int distance);

signals:
	/*! Send an event to the server. FIXME : The event is not destroyed for the moment */
	void postEvent(const Event* event);

public slots:
	void loadAndPruneChunks();

protected:
	Me* m_me;
	QList<ChunkPostition> m_loadedChunks;
	int i_viewDistance;
};

#endif // SERVERCONNECTOR_H
