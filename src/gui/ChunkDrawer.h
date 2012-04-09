#ifndef CHUNKDRAWER_H
#define CHUNKDRAWER_H

#include "OpenGL.h"

class BlockInfo;
class Chunk;

class ChunkDrawer
{
public:
	ChunkDrawer(Chunk* chunkToDraw);
	~ChunkDrawer();

	void generateVBO();
	void render();
private:
	enum CubeFace {
		CubeFace_Front = 0,
		CubeFace_Left = 15,
		CubeFace_Bottom = 30,
		CubeFace_Right = 45,
		CubeFace_Top = 60,
		CubeFace_Back = 75
	};

	void drawFace(const CubeFace face, BlockInfo* block, const int wx, const int wy, const int wz);

	Chunk* m_chunkToDraw;
	GLuint i_bufferVertex, i_bufferIndices;

	GLfloat* f_array;
	int i_arraySize;
	GLuint* i_indiceArray;
	int i_indiceArraySize;
};

#endif // CHUNKDRAWER_H
