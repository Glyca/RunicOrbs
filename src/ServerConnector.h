#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <QList>

#include "EventReadyObject.h"
#include "Me.h"
#include "World.h"

class BaseEvent;

/*! The ServerConnector class is a gate to a Server */
class ServerConnector : public EventReadyObject
{
	Q_OBJECT
public:
	explicit ServerConnector(Server* serverToConnect);
	virtual ~ServerConnector();

	/*! Connect to the server. Must be called before everything else.
		\returns true if connection succeeded */
	bool connect();

	World* world();

	/*! Send an event to the Server this ServerConnector is connected to.
		If it is a ClientServer, the event will be send over the network. */
	void postEventToServer(BaseEvent* event);

	/*! Return a pointer to the Player the player is */
	Me* me();

	/*! Mine the pointed block */
	void pickBlock();
	/*! Place a block on the pointed emplacement */
	void useBlock();

	void setViewDistance(const int distance);

	/*! Request a new chunk to be loaded */
	void loadChunk(const ChunkPosition& chunkPosition);
	/*! Request a chunk to be unloaded */
	void unloadChunk(const ChunkPosition& chunkPosition);

signals:
	/*! Fired when connected to the server */
	void connected();

public slots:
	/*! Load and unload chunks arround the player */
	void loadAndPruneChunks();

	void playerReceivedEvent(BaseEvent* baseEvent);

private:
	Server* m_server; //!< The server we are talking to
	int i_worldId; //!< The current World id
	int i_playerId; //!< The current Player id
	QList<ChunkPosition> m_loadedChunks; //!< The chunks we loaded
	int i_viewDistance;
};

#endif // SERVERCONNECTOR_H
