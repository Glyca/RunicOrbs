#ifndef BLOCKUSEEVENT_H
#define BLOCKUSEEVENT_H

#include "PlayerEvent.h"

class BlockUseEvent : public PlayerEvent
{
public:
	BlockUseEvent(const BlockPosition& position, Player* player);

	virtual void perform(Server& server) const;
	virtual QByteArray serialize() const;

protected:
	BlockPosition m_blockPosition;
};

#endif // BLOCKUSEEVENT_H
