#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <QObject>
#include <QList>

#include "Me.h"
#include "World.h"

class ClientEvent;
class ServerEvent;

/*! The ServerConnector class is a gate to a Server */
class ServerConnector : public QObject
{
	Q_OBJECT
public:
	explicit ServerConnector(QObject *parent = 0);

	virtual World& world();

	inline Me* me() const {return m_me;}

	void pickBlock();
	void useBlock();
	void selectSlot(const int selectedSlot);

	void setViewDistance(const int distance);

	/*! Emit signal refreshInventory() */
	inline void makeInventoryRefreshed() {emit refreshInventory();}

signals:
	/*! Send an event to a Server, such as a remote Server. FIXME : The Event is not destroyed for the moment */
	void postEvent(const ServerEvent* event);

	/*! Fired when we must redraw the inventory */
	void refreshInventory();

public slots:
	/*! Perform the event for the client (may be received from the network) */
	void takeEvent(const ClientEvent* event);
	/*! Load and unload chunks arround the player */
	void loadAndPruneChunks();

protected:
	Me* m_me;
	QList<ChunkPosition> m_loadedChunks; //!< The chunks we loaded
	int i_viewDistance;
};

#endif // SERVERCONNECTOR_H
