#include "ChunkDrawer.h"
#include "blocks/Blocks.h"
#include "blocks/BlockDescriptor.h"
#include "Chunk.h"
#include "World.h"

#define BUFFER_OFFSET(a) ((char*)NULL + (a))
#define BUFFER_OFFSET_FLOAT(a) (BUFFER_OFFSET(a * sizeof(GLfloat)))

const int VECTOR_SIZE = 3; // Since we are in 3D
const int VECTOR_PER_VERTEX = 3; // One for postion, one for normal, and one for color
const int VERTEX_PER_FACE = 4; // 4 vertex are needed to draw a face
const int CUBE_FACES = 6;
// How WILL BE stored our array in VRAM :
// [ VNC VNC VNC VNC ] [ VNC VNC VNC VNC ] [ VNC VNC VNC VNC ]... (NUMBER_OF_CUBE_FACES=6 times per cube)

ChunkDrawer::ChunkDrawer(Chunk* chunkToDraw) : m_chunkToDraw(chunkToDraw), i_arraySize(0), i_indiceArraySize(0)
{
	glGenBuffers(1, &i_bufferVertex);
	glGenBuffers(1, &i_bufferIndices);
}

ChunkDrawer::~ChunkDrawer()
{
	glDeleteBuffers(1, &i_bufferVertex);
	glDeleteBuffers(1, &i_bufferIndices);
}

void ChunkDrawer::generateVBO()
{
	// Firstly we create a table with the max size (ie. all blacks may be drawn, so we allocate space for all)
	// Each vertex has 3 vectors for position, 3 for normal and 3 for color. And each face has 4 vertex. And each cube has 6 faces.
	f_array = new GLfloat[8 * VERTEX_PER_FACE * CUBE_FACES * CHUNK_X_SIZE * CHUNK_Y_SIZE * CHUNK_Z_SIZE];
	i_arraySize = 0; // and we say there is 0 bytes inside for now

	i_indiceArray = new GLuint[VECTOR_PER_VERTEX * VERTEX_PER_FACE * CUBE_FACES * CHUNK_X_SIZE * CHUNK_Y_SIZE * CHUNK_Z_SIZE];
	i_indiceArraySize = 0;

	for(int k = 0; k < CHUNK_Z_SIZE; k++)
	{
		for(int i = 0; i < CHUNK_X_SIZE; i++)
		{
			for(int j = 0; j < CHUNK_HEIGHT; j++)
			{
				int wi, wj, wk; // These are the coordinates in the world
				m_chunkToDraw->mapToWorld(i, j, k, wi, wj, wk);

				BlockInfo* block = m_chunkToDraw->block(i, j, k);

				if(!block->isVoid()) // Really, we don't draw the air
				{// Only render visible geometry
					// Front face
					if(!m_chunkToDraw->world().block(BlockPosition(wi, wj, wk - 1))->descriptor().isCube() || *block == Blocks::TORCH) {
						drawFace(CubeFace_Front, block, wi, wj, wk);
					}
					// Left face
					if(!m_chunkToDraw->world().block(BlockPosition(wi - 1, wj, wk))->descriptor().isCube() || *block == Blocks::TORCH) {
						drawFace(CubeFace_Left, block, wi, wj, wk);
					}
					// Bottom face
					if(j != 0 && (!m_chunkToDraw->world().block(BlockPosition(wi, wj - 1, wk))->descriptor().isCube() || *block == Blocks::TORCH)) {
						drawFace(CubeFace_Bottom, block, wi, wj, wk);
					}
					// Right face
					if(!m_chunkToDraw->world().block(BlockPosition(wi + 1, wj, wk))->descriptor().isCube() || *block == Blocks::TORCH) {
						drawFace(CubeFace_Right, block, wi, wj, wk);
					}
					// Top face
					if(!m_chunkToDraw->world().block(BlockPosition(wi, wj + 1, wk))->descriptor().isCube() || *block == Blocks::TORCH) {
						drawFace(CubeFace_Top, block, wi, wj, wk);
					}
					// Back face
					if(!m_chunkToDraw->world().block(BlockPosition(wi, wj, wk + 1))->descriptor().isCube() || *block == Blocks::TORCH) {
						drawFace(CubeFace_Back, block, wi, wj, wk);
					}
				}
			} // j
		} // i
	} // k

	// Buffer d'informations de vertex
	glBindBuffer(GL_ARRAY_BUFFER, i_bufferVertex);
	glBufferData(GL_ARRAY_BUFFER, i_arraySize * sizeof(GLfloat), f_array, GL_STATIC_DRAW); // Send data
	// We finished to upload our vertex, so we can delete the temp array
	delete[] f_array;

	// Buffer d'indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_bufferIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_indiceArraySize * sizeof(GLuint), i_indiceArray, GL_STATIC_DRAW); // Send data
	delete[] i_indiceArray;
}

void ChunkDrawer::render()
{
	// Utilisation des données des buffers
	glBindBuffer(GL_ARRAY_BUFFER, i_bufferVertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_bufferIndices);
	glVertexPointer(3, // Coordinates per vertex
					GL_FLOAT, // Data type
					8*sizeof(GLfloat), // Offset between each vertice
					BUFFER_OFFSET_FLOAT(0)); // where is the first vertice


	glColorPointer(3, // Coordinates per color
				   GL_FLOAT, // Data type
				   8*sizeof(GLfloat), // Offset between each color
				   BUFFER_OFFSET_FLOAT(3)); // where is the first color

	glTexCoordPointer(2, // Coordinates per texture coordinate
					  GL_FLOAT, // Data type
					  8*sizeof(GLfloat), // Offset between each texture coordinate
					  BUFFER_OFFSET_FLOAT(6)); // where is the first texture coordinate

	// Activation d'utilisation des tableaux
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	// Rendu de notre géométrie
	glDrawElements(GL_QUADS, i_indiceArraySize, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Désactivation des tableaux
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );

	// Safely disbale buffers (for other compenents of the program)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ChunkDrawer::drawFace(const CubeFace face, BlockInfo* block, const int wx, const int wy, const int wz)
{
	static const GLfloat cubeVertexAndNormals[CUBE_FACES * 5 * VECTOR_SIZE] = {
		// The origin of the cube is 0, it is drawed in the positives values
		//	  v6----- v5
		//	 /|      /|
		// Oy------v0 |
		// |  |     | |
		// |  |Oz---|-|v4
		// | /      |/
		// 0-------Ox

		//       V E R T E X                                            | NORMAL (same for one face)
		// Front face
		0.0f,0.0f,0.0f, 1.0f,0.0f,0.0f, 1.0f,1.0f,0.0f, 0.0f,1.0f,0.0f,   0.0f ,0.0f ,-1.0f,   // 15
		// Left face
		0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f, 0.0f,1.0f,1.0f, 0.0f,0.0f,1.0f,   -1.0f,0.0f ,0.0f,
		// Bottom face
		0.0f,0.0f,0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,1.0f, 1.0f,0.0f,0.0f,   0.0f ,-1.0f,0.0f,
		// Right face
		1.0f,0.0f,0.0f, 1.0f,0.0f,1.0f, 1.0f,1.0f,1.0f, 1.0f,1.0f,0.0f,   1.0f ,0.0f ,0.0f,
		// Top face
		1.0f,1.0f,0.0f, 0.0f,1.0f,0.0f, 0.0f,1.0f,1.0f, 1.0f,1.0f,1.0f,   0.0f ,1.0f ,0.0f,
		// Back face
		1.0f,1.0f,1.0f, 0.0f,1.0f,1.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,1.0f,   0.0f ,0.0f ,1.0f,
	};

	// For the 4 vectors of the face
	for(int v = 0; v < VERTEX_PER_FACE; v++)
	{
		// Vertex
		if(*block == Blocks::TORCH) { // Draw a torch
			f_array[i_arraySize + 0] = cubeVertexAndNormals[face + v*3 + 0]/5.0f + 0.40f + wx;
			f_array[i_arraySize + 1] = cubeVertexAndNormals[face + v*3 + 1]/1.1f + wy;
			f_array[i_arraySize + 2] = cubeVertexAndNormals[face + v*3 + 2]/5.0f + 0.40f + wz;
		}
		else { // Simply draw a cube
			f_array[i_arraySize + 0] = cubeVertexAndNormals[face + v*3 + 0] + wx;
			f_array[i_arraySize + 1] = cubeVertexAndNormals[face + v*3 + 1] + wy;
			f_array[i_arraySize + 2] = cubeVertexAndNormals[face + v*3 + 2] + wz;
		}
		i_arraySize += 3;

		// Color (full white until lighting)
		f_array[i_arraySize + 0] = 1.0f; // R
		f_array[i_arraySize + 1] = 1.0f; // V
		f_array[i_arraySize + 2] = 1.0f; // B
		int lightLevel = 0;
		switch(face) {
		case CubeFace_Front:

			break;
		case CubeFace_Left:

			break;
		case CubeFace_Bottom:

			break;
		case CubeFace_Right:

			break;
		case CubeFace_Top:

			break;
		case CubeFace_Back:

			break;
		}
		i_arraySize += 3;

		// Texture
		TexCoords* textureCoordinates = block->descriptor().getTexture();
		f_array[i_arraySize + 0] = textureCoordinates[v].tx;
		f_array[i_arraySize + 1] = textureCoordinates[v].ty;
		i_arraySize += 2;

		i_indiceArray[i_indiceArraySize] = i_indiceArraySize;
		i_indiceArraySize++;
	}
}
