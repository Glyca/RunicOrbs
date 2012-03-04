#ifndef CHUNKDRAWER_H
#define CHUNKDRAWER_H

#include <QtOpenGL>

#include "Chunk.h"

class ChunkDrawer
{
public:
	ChunkDrawer(Chunk* chunkToDraw);
	~ChunkDrawer();

	void generateVBO();
	void render();
private:

	Chunk* m_chunkToDraw;
	GLuint i_bufferVertex, i_bufferIndices;

	int i_arraySize;
	int i_indiceArraySize;
};

#endif // CHUNKDRAWER_H
