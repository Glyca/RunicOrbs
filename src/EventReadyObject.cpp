#include <QEvent>

#include "server/events/BaseEvent.h"
#include "server/events/BlockEvent.h"
#include "server/events/EventIds.h"
#include "EventReadyObject.h"
#include "Log.h"

EventReadyObject::EventReadyObject(QObject* parent) : QObject(parent)
{
}

EventReadyObject::~EventReadyObject()
{
}

bool EventReadyObject::event(QEvent* event)
{
	// If this is a The Runic Orbs event
	BaseEvent* theBaseEvent = dynamic_cast<BaseEvent*>(event);
	if(theBaseEvent != 0)
	{
		BlockEvent* theBlockEvent = dynamic_cast<BlockEvent*>(theBaseEvent);
		if(theBlockEvent != 0)  // event IS_A BlockEvent
		{
			if(blockEvent(theBlockEvent) || chunkEvent(theBlockEvent) || worldEvent(theBlockEvent)) { // If the BlockEvent is handled
				return true;
			}
		}

		ChunkEvent* theChunkEvent = dynamic_cast<ChunkEvent*>(theBaseEvent);
		if(theChunkEvent != 0)  // event IS_A ChunkEvent
		{
			if(chunkEvent(theChunkEvent) || worldEvent(theChunkEvent)) { // If the ChunkEvent is handled
				return true;
			}
		}

		WorldEvent* theWorldEvent = dynamic_cast<WorldEvent*>(theBaseEvent);
		if(theWorldEvent != 0) // event IS_A WorldEvent
		{
			if(worldEvent(theWorldEvent)) { // If the WorldEvent is handled
				return true;
			}
		}

		if(baseEvent(theBaseEvent)) return true; // If the BaseEvent is handled
	}

	return QObject::event(event);
}

bool EventReadyObject::baseEvent(BaseEvent* baseEvent)
{
	Q_UNUSED(baseEvent);
	return false;
}

bool EventReadyObject::worldEvent(WorldEvent* worldEvent)
{
	Q_UNUSED(worldEvent);
	return false;
}

bool EventReadyObject::chunkEvent(ChunkEvent* chunkEvent)
{
	Q_UNUSED(chunkEvent);
	return false;
}

bool EventReadyObject::blockEvent(BlockEvent* blockEvent)
{
	Q_UNUSED(blockEvent);
	return false;
}

void EventReadyObject::connectPlayer(Player* player)
{
	int playerId = player->id();
	if(m_players.contains(playerId))
	{
		lwarning(Channel_Server, tr("Player #%1 is already connected to this object %2").arg(playerId).arg(metaObject()->className()));
		return;
	}
	m_players.insert(playerId, player);
}

Player* EventReadyObject::player(int playerId) const
{
	Player* player =  m_players.value(playerId, NULL);
	if(player == NULL) // The Player is not connected to this EventReadyObject
	{
		foreach (QObject* child, this->children()) // Check in children
		{
			if(dynamic_cast<EventReadyObject*>(child) != 0) // Is there is a child EventReadyObject ?
			{
				player = reinterpret_cast<EventReadyObject*>(child)->player(playerId);

				if(player != NULL) // Has it the player requested ?
				{
					return player;
				}
			}
		}
	}
	return player;
}

void EventReadyObject::sendEventToPlayers(BaseEvent* baseEvent) const
{
	foreach(Player* player, m_players)
	{
		QCoreApplication::sendEvent(player, baseEvent);
	}
}

void EventReadyObject::disconnectPlayer(int playerId)
{
	m_players.remove(playerId);
}
