#include "ChunkDrawer.h"
#include "blocks/Blocks.h"
#include "blocks/BlockDescriptor.h"
#include "blocks/TorchBlock.h"
#include "Chunk.h"
#include "OpenGLBuffer.h"
#include "World.h"

ChunkDrawer::ChunkDrawer(Chunk* chunkToDraw) : m_chunkToDraw(chunkToDraw)
{
	connect(chunkToDraw, SIGNAL(dirtied()), this, SLOT(generateVBO()), Qt::QueuedConnection);
	connect(chunkToDraw, SIGNAL(activated()), this, SLOT(generateVBO()), Qt::QueuedConnection);

	m_currentOglBuffer = new OpenGLBuffer(GL_QUADS);

	m_workingThread = new QThread();
	connect(m_workingThread, SIGNAL(finished()), m_workingThread, SLOT(deleteLater())); // The thread will auto-destroy
	this->moveToThread(m_workingThread);
	m_workingThread->start();
}

ChunkDrawer::~ChunkDrawer()
{
	m_workingThread->exit();
	delete m_currentOglBuffer;
}

void ChunkDrawer::generateVBO()
{
	if(m_chunkToDraw->state() != Chunk::ChunkState_Active) return;

	OpenGLBuffer* newOglBuffer = new OpenGLBuffer(GL_QUADS);
	newOglBuffer->preventUpload(true); // Indicates to "don't upload the geometry in video memory until we finished to generate it".

	World& workingWorld = m_chunkToDraw->world();
	int zi, zj, zk; // These are the coordinates of the zero (0;0;0) block of the chunk (in chunk relative coordinates of course)
	m_chunkToDraw->mapToWorld(0, 0, 0, zi, zj, zk);
	BlockSet blockSet;

	// *********************************************************************************************
	// STEP ONE : draw blocks at chunk boudaries (that is to say x=0, y=0, z=0, x=CHUNK_X_SIZE, ...)
	// *********************************************************************************************

	// x=0
	for(int k = 0; k < CHUNK_Z_SIZE; ++k) // z
	{
		for(int j = 1; j < CHUNK_HEIGHT - 1; ++j) // y, altitude
		{
			const int i = 0;

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

			blockSet.position = BlockPosition(zi + i, zj + j, zk + k);
			blockSet.block->descriptor().render(*newOglBuffer, blockSet);
		}
	}

	// y=0
	for(int i = 0; i < CHUNK_X_SIZE; ++i) // x
	{
		for(int k = 0; k < CHUNK_Z_SIZE; ++k) // z
		{
			const int j = 0;

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

			blockSet.position = BlockPosition(zi + i, zj + j, zk + k);
			blockSet.block->descriptor().render(*newOglBuffer, blockSet);
		}
	}

	// z=0
	for(int i = 0; i < CHUNK_X_SIZE; ++i) // x
	{
		for(int j = 0; j < CHUNK_HEIGHT; ++j) // y, altitude
		{
			const int k = 0;

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

			blockSet.position = BlockPosition(zi + i, zj + j, zk + k);
			blockSet.block->descriptor().render(*newOglBuffer, blockSet);
		}
	}

	// x=CHUNK_X_SIZE
	for(int k = 0; k < CHUNK_Z_SIZE; ++k) // z
	{
		for(int j = 1; j < CHUNK_HEIGHT; ++j) // y, altitude
		{
			const int i = CHUNK_X_SIZE - 1;

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

			blockSet.position = BlockPosition(zi + i, zj + j, zk + k);
			blockSet.block->descriptor().render(*newOglBuffer, blockSet);
		}
	}

	// y=CHUNK_Y_SIZE
	for(int i = 0; i < CHUNK_X_SIZE; ++i) // x
	{
		for(int k = 0; k < CHUNK_Z_SIZE; ++k) // z
		{
			const int j = CHUNK_Y_SIZE - 1;

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

			blockSet.position = BlockPosition(zi + i, zj + j, zk + k);
			blockSet.block->descriptor().render(*newOglBuffer, blockSet);
		}
	}

	// z=CHUNK_Z_SIZE
	for(int i = 0; i < CHUNK_X_SIZE; ++i) // x
	{
		const int k = CHUNK_Z_SIZE - 1;
		for(int j = 0; j < CHUNK_HEIGHT - 1; ++j) // y, altitude
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

			blockSet.position = BlockPosition(zi + i, zj + j, zk + k);
			blockSet.block->descriptor().render(*newOglBuffer, blockSet);
		}
	}

	// ************************************************************************************************
	// STEP TWO : draw blocks at the middle of the chunk (avoid many World::block() slow function call)
	// ************************************************************************************************

	for(int k = 1; k < CHUNK_Z_SIZE - 1; ++k) // z
	{
		for(int i = 1; i < CHUNK_X_SIZE - 1; ++i) // x
		{
			blockSet.block = m_chunkToDraw->block(i, 0, k);

			blockSet.frontBlock = m_chunkToDraw->block(i, 0, k - 1);
			blockSet.leftBlock = m_chunkToDraw->block(i - 1, 0, k);
			blockSet.rightBlock = m_chunkToDraw->block(i + 1, 0, k);
			blockSet.backBlock = m_chunkToDraw->block(i, 0, k + 1);

			blockSet.topBlock = m_chunkToDraw->block(i, 0 + 1, k);

			blockSet.topFrontBlock = m_chunkToDraw->block(i, 0 + 1, k - 1);
			blockSet.topLeftBlock = m_chunkToDraw->block(i - 1, 0 + 1, k);
			blockSet.topRightBlock = m_chunkToDraw->block(i + 1, 0 + 1, k);
			blockSet.topBackBlock = m_chunkToDraw->block(i, 0 + 1, k + 1);

			blockSet.topFrontLeftBlock = m_chunkToDraw->block(i - 1, 0 + 1, k - 1);
			blockSet.topFrontRightBlock = m_chunkToDraw->block(i + 1, 0 + 1, k - 1);
			blockSet.topBackLeftBlock = m_chunkToDraw->block(i - 1, 0 + 1, k + 1);
			blockSet.topBackRightBlock = m_chunkToDraw->block(i + 1, 0 + 1, k + 1);

			blockSet.bottomBlock = m_chunkToDraw->block(i, 0 - 1, k);

			for(int j = 1; j < CHUNK_HEIGHT - 1; ++j) // y, altitude
			{
				pushBlockSetUpwards(blockSet);

				blockSet.topBlock = m_chunkToDraw->block(i, j + 1, k);

				blockSet.topFrontBlock = m_chunkToDraw->block(i, j + 1, k - 1);
				blockSet.topLeftBlock = m_chunkToDraw->block(i - 1, j + 1, k);
				blockSet.topRightBlock = m_chunkToDraw->block(i + 1, j + 1, k);
				blockSet.topBackBlock = m_chunkToDraw->block(i, j + 1, k + 1);

				blockSet.topFrontLeftBlock = m_chunkToDraw->block(i - 1, j + 1, k - 1);
				blockSet.topFrontRightBlock = m_chunkToDraw->block(i + 1, j + 1, k - 1);
				blockSet.topBackLeftBlock = m_chunkToDraw->block(i - 1, j + 1, k + 1);
				blockSet.topBackRightBlock = m_chunkToDraw->block(i + 1, j + 1, k + 1);

				blockSet.position = BlockPosition(zi + i, zj + j, zk + k);
				blockSet.block->descriptor().render(*newOglBuffer, blockSet);
			} // j
		} // i
	} // k

	// Be sure of the order of what happens below because of multithreading (execution can stop at any time at every line)
	OpenGLBuffer* oldOglBuffer = m_currentOglBuffer;
	m_currentOglBuffer = newOglBuffer; // At this point, nothing will be drawn (new buffer isn't uploaded into vram)
	newOglBuffer->preventUpload(false); // Now video memory can be updated freely (new buffer will be uploaded in vram and drawn)

	m_oglBuffersToDestroyMutex.lock();
	m_oglBuffersToDestroy.push_back(oldOglBuffer);
	m_oglBuffersToDestroyMutex.unlock();
}

void ChunkDrawer::render()
{
	m_oglBuffersToDestroyMutex.lock();
	foreach(OpenGLBuffer* oglBuffer, m_oglBuffersToDestroy) {
		m_oglBuffersToDestroy.removeOne(oglBuffer);
		delete oglBuffer;
	}
	m_oglBuffersToDestroyMutex.unlock();

	m_currentOglBuffer->render();
}

void ChunkDrawer::pushBlockSetUpwards(BlockSet& blockSet) const
{
	blockSet.bottomBlock = blockSet.block;

	blockSet.block = blockSet.topBlock;

	blockSet.frontBlock = blockSet.topFrontBlock;
	blockSet.leftBlock = blockSet.topLeftBlock;
	blockSet.rightBlock = blockSet.topRightBlock;
	blockSet.backBlock = blockSet.topBackBlock;
}
