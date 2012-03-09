#include "ChunkDrawer.h"
#include "blocks/Blocks.h"
#include "glextensions.h"

#define BUFFER_OFFSET(a) ((char*)NULL + (a))
#define BUFFER_OFFSET_INT(a) (BUFFER_OFFSET(a * sizeof(GLfloat)))

const int VECTOR_SIZE = 3; // Since we are in 3D
const int VECTOR_PER_VERTEX = 3; // One for postion, one for normal, and one for color
const int VERTEX_PER_FACE = 4; // 4 vertex are needed to draw a face
const int CUBE_FACES = 6;
// How WILL BE stored our array in VRAM :
// [ VNC VNC VNC VNC ] [ VNC VNC VNC VNC ] [ VNC VNC VNC VNC ]... (NUMBER_OF_CUBE_FACES=6 times per cube)
//

// The following array will absolutely not be as is in vram, it's just here for easy setup.
GLfloat cubeVertexAndNormals[CUBE_FACES * 5 * VECTOR_SIZE] = {
	// The origin of the cube is 0, it is drawed in the positives values
	//	  v6----- v5
	//	 /|      /|
	// Oy------v0 |
	// |  |     | |
	// |  |Oz---|-|v4
	// | /      |/
	// 0-------Ox

	//       V E R T E X        |  NORMAL (same for one face)
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

const int INDICES_TOTAL_SIZE = VERTEX_PER_FACE * CUBE_FACES;

GLuint cubeIndices[INDICES_TOTAL_SIZE] = {
	0,1,2,3,
	4,5,6,7,
	8,9,10,11,
	12,13,14,15,
	16,17,18,19,
	20,21,22,23
};

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
	GLfloat* f_array = new GLfloat[VECTOR_SIZE * VECTOR_PER_VERTEX * VERTEX_PER_FACE * CUBE_FACES * CHUNK_X_SIZE * CHUNK_Y_SIZE * CHUNK_Z_SIZE];
	i_arraySize = 0; // and we say there is 0 bytes inside for now

	GLuint* i_indiceArray = new GLuint[INDICES_TOTAL_SIZE * CHUNK_X_SIZE * CHUNK_Y_SIZE * CHUNK_Z_SIZE];
	i_indiceArraySize = 0;

	int i_thCubeDrawed = 0; // th cube drawed (0 now)

	for(int k = 0; k < CHUNK_Z_SIZE; k++)
	{
		for(int i = 0; i < CHUNK_X_SIZE; i++)
		{
			for(int j = 0; j < CHUNK_HEIGHT; j++)
			{
				int wi, wj, wk; // These are the coordinates in the world
				m_chunkToDraw->mapToWorld(i, j, k, wi, wj, wk);

				int i_arrayOffset = i_thCubeDrawed * (VECTOR_SIZE * VECTOR_PER_VERTEX * VERTEX_PER_FACE * CUBE_FACES);

				if(*m_chunkToDraw->block(i, j, k) != Blocks::AIR) // Really, we don't draw the air
				{
					for(int face = 0; face < CUBE_FACES; face++)
					{
						int i_faceOffset = i_arrayOffset + face * VECTOR_SIZE * VECTOR_PER_VERTEX * VERTEX_PER_FACE;

						for(int v = 0; v < 4; v++) // A face has 4 vertex, for each of them, we will take the vertex postion, its normal and set a color
						{
							int i_vertexOffset = i_faceOffset + v * VECTOR_SIZE * VECTOR_PER_VERTEX;

							// Translate postion of the vertex
							f_array[i_vertexOffset + 0] = cubeVertexAndNormals[face * 15 + v * 3 + 0] + (GLfloat)wi;
							f_array[i_vertexOffset + 1] = cubeVertexAndNormals[face * 15 + v * 3 + 1] + (GLfloat)wj;
							f_array[i_vertexOffset + 2] = cubeVertexAndNormals[face * 15 + v * 3 + 2] + (GLfloat)wk;

							// Then translate and add postion of the normals
							f_array[i_vertexOffset + 3] = cubeVertexAndNormals[face * 15 + 4 * 3 + 0] + (GLfloat)wi;
							f_array[i_vertexOffset + 4] = cubeVertexAndNormals[face * 15 + 4 * 3 + 1] + (GLfloat)wj;
							f_array[i_vertexOffset + 5] = cubeVertexAndNormals[face * 15 + 4 * 3 + 2] + (GLfloat)wk;

							// Then set the 3 components of the color

							if(*m_chunkToDraw->block(i, j, k) == Blocks::STONE)
							{
								f_array[i_vertexOffset + 6] = 0.48828125f; // R
								f_array[i_vertexOffset + 7] = 0.48828125f; // V
								f_array[i_vertexOffset + 8] = 0.48828125f; // B
							}
							else if(*m_chunkToDraw->block(i, j, k) == Blocks::DIRT)
							{
								f_array[i_vertexOffset + 6] = 0.5f; // R
								f_array[i_vertexOffset + 7] = 0.28515625f; // V
								f_array[i_vertexOffset + 8] = 0.2265625f; // B
							}
							else
							{
								f_array[i_vertexOffset + 6] = 0.9f; // R
								f_array[i_vertexOffset + 7] = 0.98515625f; // V
								f_array[i_vertexOffset + 8] = 0.9265625f; // B
							}
						}
					}
					for(int n = 0; n < INDICES_TOTAL_SIZE; n++) // We basically translate the indices by INDICES_TOTAL_SIZE
					{
						i_indiceArray[i_thCubeDrawed * INDICES_TOTAL_SIZE + n] = cubeIndices[n] + i_thCubeDrawed * INDICES_TOTAL_SIZE;
					}
					// We have drawed a cube :
					i_arraySize += VECTOR_SIZE * VECTOR_PER_VERTEX * VERTEX_PER_FACE * CUBE_FACES;
					i_indiceArraySize += INDICES_TOTAL_SIZE;
					i_thCubeDrawed++;
				} // if(*m_chunkToDraw->block(i, j, k) != AIR)
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
					9*sizeof(GLfloat), // Offset between each vertice
					BUFFER_OFFSET(0)); // where is the first vertice

	glColorPointer(3, // Coordinates per color
				   GL_FLOAT, // Data type
				   9*sizeof(GLfloat), // Offset between each color
				   BUFFER_OFFSET(6*sizeof(GLfloat))); // where is the first color */

	glNormalPointer(GL_FLOAT, // Data type
					9*sizeof(GLfloat), // Offset between each normal
					BUFFER_OFFSET(3*sizeof(GLfloat))); // where is the first normal

	// Activation d'utilisation des tableaux
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );

	// Rendu de notre géométrie
	glDrawElements(GL_QUADS, i_indiceArraySize, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	// Désactivation des tableaux
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );

	// Safely disbale buffers (for other compenents of the program)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
