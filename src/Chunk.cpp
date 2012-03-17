#include "Chunk.h"
#include "gui/ChunkDrawer.h"

Chunk::Chunk(QObject *parent, QPair<int, int> position) : QObject(parent), b_dirty(true), m_position(position), m_chunkDrawer(NULL)
{
	int size = CHUNK_X_SIZE * CHUNK_Z_SIZE * CHUNK_Y_SIZE;
	p_BlockInfos = new BlockInfo[size];
}

Chunk::~Chunk()
{
	delete m_chunkDrawer;
	delete[] p_BlockInfos;
}

void Chunk::render3D()
{
	if(m_chunkDrawer == NULL) {
		m_chunkDrawer = new ChunkDrawer(this);
	}

	if(b_dirty) {
		m_chunkDrawer->generateVBO();
		b_dirty = false;
	}

	m_chunkDrawer->render(); // Incredibly fast !
}
