#ifndef BLOCKPICKEVENT_H
#define BLOCKPICKEVENT_H

#include "PlayerEvent.h"

const int EVENTID_BLOCKPICK = 1;

class BlockPickEvent : public PlayerEvent
{
public:
	BlockPickEvent(const BlockPosition& position, Player* player);

	inline virtual int id() {return EVENTID_BLOCKPICK;}

	virtual void perform(Server& server) const;
	virtual QByteArray serialize() const;

protected:
	BlockPosition m_blockPosition;
};

#endif // BLOCKPICKEVENT_H
