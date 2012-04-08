#include "BlockUseEvent.h"
#include "server/Server.h"

BlockUseEvent::BlockUseEvent(const BlockPosition& position, Player* player) : PlayerEvent(player), m_blockPosition(position)
{
}

void BlockUseEvent::perform(Server& server) const
{
	int blockId = m_player->inventorySlot(m_player->selectedSlot()).id();
	// If there is not already a block here the player has a block of this id in stock
	if(server.world().block(m_blockPosition)->isVoid() && m_player->takeOne(blockId)) {
		server.world().block(m_blockPosition)->setId(blockId);
		server.world().chunk(m_blockPosition)->makeDirty();
	}
}

QByteArray BlockUseEvent::serialize() const
{
	// TODO
	QByteArray byteArray;

	return byteArray;
}
