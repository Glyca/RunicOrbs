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

	int i_vertexArraySize;
	GLfloat* f_vertexArray;

	int i_indiceArraySize;
	GLuint* i_indiceArray;
};

#endif // CHUNKDRAWER_H
