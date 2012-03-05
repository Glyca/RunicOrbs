#include "LocalServerConnector.h"

#include <QDebug>

LocalServerConnector::LocalServerConnector()
{
	qDebug() << "Initialized" << metaObject()->className();
	connect(&world(), SIGNAL(chunkLoaded(ChunkPostition)), this, SLOT(onChunkLoaded(ChunkPostition)));
}

void LocalServerConnector::onChunkLoaded(ChunkPostition position)
{
	if(world().chunk(position) == world().chunk(me()->v_position)) // If this is the chunk the player is standing on
	{
		// Then load some chunks arround
		const int chunksLoadPseudoRadius = 2;
		for(int x = - chunksLoadPseudoRadius; x <= chunksLoadPseudoRadius; x++)
		{
			for(int z = - chunksLoadPseudoRadius; z <= chunksLoadPseudoRadius; z++)
			{
				world().loadChunk(ChunkPostition(position.first + x, position.second + z));
			}
		}
	}
}

