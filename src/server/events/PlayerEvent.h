#ifndef PLAYEREVENT_H
#define PLAYEREVENT_H

#include "ServerEvent.h"
#include "Player.h"

/*! An abstract class for an event which concerns a player */
class PlayerEvent : public ServerEvent
{
public:
	PlayerEvent(Player* player);

protected:
	Player* m_player; // The player concerned by the event
};

#endif // PLAYEREVENT_H
