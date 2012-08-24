#ifndef EVENTREADYOBJECT_H
#define EVENTREADYOBJECT_H

#include <QCoreApplication>
#include <QMap>

#include "Player.h"

class BaseEvent;
class BlockEvent;
class ChunkEvent;
class WorldEvent;

/*! A QObject overlay with many event handlers already defined */
class EventReadyObject : public QObject
{
public:
	explicit EventReadyObject(QObject *parent = 0);
	virtual ~EventReadyObject();

	virtual bool event(QEvent* event);

	virtual bool baseEvent(BaseEvent* baseEvent);
	virtual bool worldEvent(WorldEvent* worldEvent);
	virtual bool chunkEvent(ChunkEvent* chunkEvent);
	virtual bool blockEvent(BlockEvent* blockEvent);

	/*! Add a Player to this object. Some events can be sended to it now from this object */
	void connectPlayer(Player* player);
	/*! Get the connected Player of the given id */
	Player* player(int playerId) const;
	/*! Send an event to connected players */
	void sendEventToPlayers(BaseEvent* baseEvent) const;
	/*! Disconnect a Player from this object */
	void disconnectPlayer(int playerId);

private:
	QMap<int, Player*> m_players; //!< Players who are connected to this object
};

#endif // EVENTREADYOBJECT_H
