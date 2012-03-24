#include "ChunkConnectEvent.h"
#include "server/Server.h"

ChunkConnectEvent::ChunkConnectEvent(const ChunkPostition& position, ChunkConnection connectionType) : ChunkEvent(position), m_connectionType(connectionType)
{
}


void ChunkConnectEvent::perform(Server& server) const
{
	if(m_connectionType == ChunkConnection_Connect) {
		server.world().chunk(m_chunkPosition)->activate();
	}
	else if(m_connectionType == ChunkConnection_Disconnect) {
		server.world().chunk(m_chunkPosition)->idle();
	}
}

QByteArray ChunkConnectEvent::serialize() const
{
	// TODO
	QByteArray byteArray;

	return byteArray;
}
