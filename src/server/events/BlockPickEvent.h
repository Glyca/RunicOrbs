#ifndef BLOCKPICKEVENT_H
#define BLOCKPICKEVENT_H

#include "PlayerEvent.h"

class BlockPickEvent : public PlayerEvent
{
public:
	BlockPickEvent(const BlockPosition& position, Player* player);

	virtual void perform(Server& server) const;
	virtual QByteArray serialize() const;

protected:
	BlockPosition m_blockPosition;
};

#endif // BLOCKPICKEVENT_H
