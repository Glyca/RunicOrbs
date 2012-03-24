#include "Chunk.h"
#include "gui/ChunkDrawer.h"

Chunk::Chunk(QObject *parent, ChunkPostition position) : QObject(parent), m_state(ChunkState_Idle), b_dirty(true), m_position(position), m_chunkDrawer(NULL)
{
	int size = CHUNK_X_SIZE * CHUNK_Z_SIZE * CHUNK_Y_SIZE;
	p_BlockInfos = new BlockInfo[size];
}

Chunk::~Chunk()
{
	delete m_chunkDrawer;
	delete[] p_BlockInfos;
}

void Chunk::activate()
{
	m_chunkDrawer = new ChunkDrawer(this);
	b_dirty = true; // we must redraw the chunk
	m_state = ChunkState_Active;
}

void Chunk::idle()
{
	delete m_chunkDrawer;
	m_state = ChunkState_Idle;
}

void Chunk::render3D()
{
	if(m_state == ChunkState_Active) {
		if(b_dirty) {
			m_chunkDrawer->generateVBO();
			b_dirty = false;
		}

		m_chunkDrawer->render(); // Incredibly fast !
	}
}
