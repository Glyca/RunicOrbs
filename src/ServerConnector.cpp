#include "Log.h"
#include "server/events/BlockChangedEvent.h"
#include "server/events/PlayerChunkEvent.h"
#include "server/Server.h"
#include "ServerConnector.h"

ServerConnector::ServerConnector(Server* serverToConnect)
	: EventReadyObject(reinterpret_cast<QObject*>(serverToConnect)), m_server(serverToConnect)
{
	Player* player = m_server->world()->newPlayer();
	i_playerId = player->id();
	ldebug(Channel_Server, tr("ServerConnector initialized, pid #%1").arg(i_playerId));
}

ServerConnector::~ServerConnector()
{
}

bool ServerConnector::connect()
{
	emit connected();
	return true; // TODO
}

World* ServerConnector::world()
{
	return m_server->world();
}

void ServerConnector::postEventToServer(BaseEvent* event)
{
	// Post the event to the server :
	QCoreApplication::postEvent(reinterpret_cast<QObject*>(m_server), event);
}

Me* ServerConnector::me()
{
	return static_cast<Me*>(m_server->player(i_playerId));
}

void ServerConnector::loadAndPruneChunks()
{
	ChunkPosition currentPosition = world()->chunkPosition(me()->v_position.x, me()->v_position.z);
	QList<ChunkPosition> wantedChunks; // The chunks we still want to be active

	// Create a list of the wanted chunks
	for(int x = - i_viewDistance; x < i_viewDistance+1; ++x)
	{
		for(int z = - i_viewDistance; z < i_viewDistance+1; ++z)
		{
			ChunkPosition position = ChunkPosition(currentPosition.first + x, currentPosition.second + z);
			wantedChunks.push_back(position);
		}
	}

	// Let's see if we have to prune unwanted ones...
	for (int i = 0; i < m_loadedChunks.size(); ++i) {
		ChunkPosition processingChunk = m_loadedChunks.at(i);

		// If the chunk is wanted
		if(wantedChunks.contains(processingChunk)) {
			// delete it from the wanted ones
			wantedChunks.removeOne(processingChunk);
		}
		else {
			// The chunk is unwanted, get rid of it
			unloadChunk(processingChunk);
			// Delete it from the loaded chunks list
			m_loadedChunks.removeAt(i); i--;
		}
	}

	// Now we load the chunks that were not in the loaded chunks
	for (int i = 0; i < wantedChunks.size(); ++i) {
		ChunkPosition processingChunk = wantedChunks.at(i);
		loadChunk(processingChunk);
		m_loadedChunks.push_back(processingChunk);
	}
}

void ServerConnector::loadChunk(const ChunkPosition& chunkPosition)
{
	postEventToServer(new PlayerChunkEvent(Connect_PlayerChunkEventId, i_worldId, chunkPosition, me()->id()));
}

void ServerConnector::unloadChunk(const ChunkPosition& chunkPosition)
{
	postEventToServer(new PlayerChunkEvent(Disconnect_PlayerChunkEventId, i_worldId, chunkPosition, me()->id()));
}

void ServerConnector::pickBlock()
{
	BlockPosition blockPosition = me()->pointedBlock();
	ChunkPosition chunkPosition = world()->chunkPosition(blockPosition);
	postEventToServer(new PlayerBlockEvent(Pick_PlayerBlockEventId, i_worldId, chunkPosition, blockPosition, me()->id()));
}

void ServerConnector::useBlock()
{
	BlockPosition blockPosition = me()->pointedFreeBlock();
	ChunkPosition chunkPosition = world()->chunkPosition(blockPosition);
	postEventToServer(new PlayerBlockEvent(Place_PlayerBlockEventId, i_worldId, chunkPosition, blockPosition, me()->id()));
}

void ServerConnector::selectSlot(const int selectedSlot)
{
/*	// Check that the slot id we demand is valid
	int newSelectedSlot = selectedSlot;
	if(newSelectedSlot < 0) {
		newSelectedSlot = VIEWABLE_INVENTORY_SIZE - 1;
	}
	if(newSelectedSlot >= (int)VIEWABLE_INVENTORY_SIZE) {
		newSelectedSlot = 0;
	}
	SlotSelectEvent* event = new SlotSelectEvent(newSelectedSlot, me());
	emit postEvent(event);*/
}

void ServerConnector::setViewDistance(const int distance)
{
	i_viewDistance = distance;
}
