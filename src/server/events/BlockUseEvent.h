#ifndef BLOCKUSEEVENT_H
#define BLOCKUSEEVENT_H

#include "PlayerEvent.h"

const int EVENTID_BLOCKUSE = 2;

class BlockUseEvent : public PlayerEvent
{
public:
	BlockUseEvent(const BlockPosition& position, Player* player);

	inline virtual int id() {return EVENTID_BLOCKUSE;}

	virtual void perform(Server& server) const;
	virtual QByteArray serialize() const;

protected:
	BlockPosition m_blockPosition;
};

#endif // BLOCKUSEEVENT_H
