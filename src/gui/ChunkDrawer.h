#ifndef CHUNKDRAWER_H
#define CHUNKDRAWER_H

#include "OpenGL.h"

class BlockInfo;
struct BlockSet;
class Chunk;
class OpenGLBuffer;

class ChunkDrawer
{
public:
	ChunkDrawer(Chunk* chunkToDraw);
	~ChunkDrawer();

	void generateVBO();
	void render();

private:
	/*! Put all topBlocks of the blokSet in block and alls blocks in BottomsBlocks.
	  Doing this to iterate over Y avoids a lot of block access in the world */
	void pushBlockSetUpwards(BlockSet& blockSet) const;

	Chunk* m_chunkToDraw;
	OpenGLBuffer* m_oglBuffer;
};

#endif // CHUNKDRAWER_H
