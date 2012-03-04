#include "Chunk.h"
#include "gui/ChunkDrawer.h"
#include "ChunkGenerator.h"

Chunk::Chunk(QObject *parent, QPair<int, int> position) : QObject(parent), m_position(position), m_chunkDrawer(NULL), m_chunkGenerator(NULL)
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
	if(m_chunkGenerator == NULL)
	{
		m_chunkGenerator = new ChunkGenerator(this, seed);
		m_chunkGenerator->generateChunk();
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
