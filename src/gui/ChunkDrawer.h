#ifndef CHUNKDRAWER_H
#define CHUNKDRAWER_H

#include "OpenGL.h"

class BlockInfo;
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
	Chunk* m_chunkToDraw;
	OpenGLBuffer* m_oglBuffer;
};

#endif // CHUNKDRAWER_H
