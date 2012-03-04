#include "Chunk.h"
#include "Utils.h"
#include "gui/ChunkDrawer.h"

Chunk::Chunk(QObject *parent) : QObject(parent), m_chunkDrawer(NULL)
{
	int size = CHUNK_X_SIZE * CHUNK_Z_SIZE * CHUNK_Y_SIZE;
	p_BlockInfos = new BlockInfo[size];
}

Chunk::~Chunk()
{
	delete m_chunkDrawer;
	delete p_BlockInfos;
}

void Chunk::generate(int seed)
{
	for(int j = 0; j < CHUNK_HEIGHT >> 1; j++)
	{
		for(int i = 0; i < CHUNK_X_SIZE; i++)
		{
			for(int k = 0; k < CHUNK_Z_SIZE; k++)
			{
				// On ne met que de la roche
				block(i, j, k)->setId(1);
			}
		}
	}

	for(int j = CHUNK_HEIGHT >> 1; j < CHUNK_HEIGHT - 4; j++)
	{
		for(int i = 0; i < CHUNK_X_SIZE; i++)
		{
			for(int k = 0; k < CHUNK_Z_SIZE; k++)
			{
				// On ne met que de la terre
				block(i, j, k)->setId(2);
			}
		}
	}
}

void Chunk::render3D()
{
	if(m_chunkDrawer == NULL)
	{
		m_chunkDrawer = new ChunkDrawer(this);
		m_chunkDrawer->generateVBO();
	}

	m_chunkDrawer->render(); // Incredibly fast !
}
