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
	int zi, zj, zk; // These are the coordinates of the zero (0;0;0) block of the chunk (in chunk relative coordinates of course)
	m_chunkToDraw->mapToWorld(0, 0, 0, zi, zj, zk);
	BlockSet blockSet;

	for(int k = 0; k < CHUNK_Z_SIZE; k++) // z
	{
		for(int i = 0; i < CHUNK_X_SIZE; i++) // x
		{
			for(int j = 0; j < CHUNK_HEIGHT; j++) // y, altitude
			{
				blockSet.block = m_chunkToDraw->block(i, j, k);

				blockSet.frontBlock = workingWorld.block(BlockPosition(zi + i, zj + j, zk + k - 1));
				blockSet.leftBlock = workingWorld.block(BlockPosition(zi + i - 1, zj + j, zk + k));
				blockSet.rightBlock = workingWorld.block(BlockPosition(zi + i + 1, zj + j, zk + k));
				blockSet.backBlock = workingWorld.block(BlockPosition(zi + i, zj + j, zk + k + 1));

				blockSet.topBlock = workingWorld.block(BlockPosition(zi + i, zj + j + 1, zk + k));

				blockSet.topFrontBlock = workingWorld.block(BlockPosition(zi + i, zj + j + 1, zk + k - 1));
				blockSet.topLeftBlock = workingWorld.block(BlockPosition(zi + i - 1, zj + j + 1, zk + k));
				blockSet.topRightBlock = workingWorld.block(BlockPosition(zi + i + 1, zj + j + 1, zk + k));
				blockSet.topBackBlock = workingWorld.block(BlockPosition(zi + i, zj + j + 1, zk + k + 1));

				blockSet.topFrontLeftBlock = workingWorld.block(BlockPosition(zi + i - 1, zj + j + 1, zk + k - 1));
				blockSet.topFrontRightBlock = workingWorld.block(BlockPosition(zi + i + 1, zj + j + 1, zk + k - 1));
				blockSet.topBackLeftBlock = workingWorld.block(BlockPosition(zi + i - 1, zj + j + 1, zk + k + 1));
				blockSet.topBackRightBlock = workingWorld.block(BlockPosition(zi + i + 1, zj + j + 1, zk + k + 1));

				blockSet.bottomBlock = workingWorld.block(BlockPosition(zi + i, zj + j - 1, zk + k));

				blockSet.block->descriptor().render(*m_oglBuffer, blockSet, BlockPosition(zi + i, zj + j, zk + k), workingWorld);
			} // j
		} // i
	} // k
}

void ChunkDrawer::render()
{
	m_oglBuffer->render();
}
