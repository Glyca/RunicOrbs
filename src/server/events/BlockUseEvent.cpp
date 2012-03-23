#include "BlockUseEvent.h"
#include "server/Server.h"

BlockUseEvent::BlockUseEvent(const BlockPosition& position, Player* player) : PlayerEvent(player), m_blockPosition(position)
{
}

void BlockUseEvent::perform(Server& server) const
{
	server.world().block(m_blockPosition)->setId(1);
	server.world().chunk(m_blockPosition)->makeDirty();
}

QByteArray BlockUseEvent::serialize() const
{
	// TODO
	QByteArray byteArray;

	return byteArray;
}
