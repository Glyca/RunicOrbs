#include "ChunkDrawer.h"
#include "blocks/Blocks.h"
#include "blocks/BlockDescriptor.h"
#include "blocks/TorchBlock.h"
#include "Chunk.h"
#include "OpenGLBuffer.h"
#include "World.h"

#define BUFFER_OFFSET(a) ((char*)NULL + (a))
#define BUFFER_OFFSET_FLOAT(a) (BUFFER_OFFSET(a * sizeof(GLfloat)))

const int VECTOR_SIZE = 3; // Since we are in 3D
const int VECTOR_PER_VERTEX = 3; // One for postion, one for normal, and one for color
const int VERTEX_PER_FACE = 4; // 4 vertex are needed to draw a face
const int CUBE_FACES = 6;
// How WILL BE stored our array in VRAM :
// [ VNC VNC VNC VNC ] [ VNC VNC VNC VNC ] [ VNC VNC VNC VNC ]... (NUMBER_OF_CUBE_FACES=6 times per cube)

ChunkDrawer::ChunkDrawer(Chunk* chunkToDraw) : m_chunkToDraw(chunkToDraw)
{
	m_oglBuffer = new OpenGLBuffer();
	m_oglBuffer->genBuffer();
}

ChunkDrawer::~ChunkDrawer()
{
	delete m_oglBuffer;
}

void ChunkDrawer::generateVBO()
{
	m_oglBuffer->clear();

	World& workingWorld = m_chunkToDraw->world();

	for(int k = 0; k < CHUNK_Z_SIZE; k++)
	{
		for(int i = 0; i < CHUNK_X_SIZE; i++)
		{
			for(int j = 0; j < CHUNK_HEIGHT; j++)
			{
				int wi, wj, wk; // These are the coordinates in the world
				m_chunkToDraw->mapToWorld(i, j, k, wi, wj, wk);
				BlockInfo* block = m_chunkToDraw->block(i, j, k);
				block->descriptor().render(*m_oglBuffer, *block, BlockPosition(wi, wj, wk), workingWorld);
			} // j
		} // i
	} // k
}

void ChunkDrawer::render()
{
	m_oglBuffer->render();
}
