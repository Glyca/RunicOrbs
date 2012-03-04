#include "ChunkDrawer.h"

GLfloat cubeVertexArray[24] = {
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f
};

GLuint cubeIndicesArray[36] = {
	0, 1, 2, 2, 3, 0,
	3, 2, 6, 6, 7, 3,
	7, 6, 5, 5, 4, 7,
	4, 0, 3, 3, 7, 4,
	0, 1, 5, 5, 4, 0,
	1, 5, 6, 6, 2, 1
};

ChunkDrawer::ChunkDrawer(Chunk* chunkToDraw) : m_chunkToDraw(chunkToDraw), i_vertexArraySize(0), i_indiceArraySize(0)
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
	f_vertexArray = new GLfloat[sizeof(cubeVertexArray) * CHUNK_X_SIZE * CHUNK_Y_SIZE * CHUNK_Z_SIZE];
	i_vertexArraySize = 0; // and we say there is 0 bytes inside for now

	i_indiceArray = new GLuint[sizeof(cubeIndicesArray) * CHUNK_X_SIZE * CHUNK_Y_SIZE * CHUNK_Z_SIZE];
	i_indiceArraySize = 0;

	int i_thCubeDrawed = 0; // th cube drawed (0 now)

	for(int j = 0; j < CHUNK_HEIGHT; j++)
	{
		for(int i = 0; i < CHUNK_X_SIZE; i++)
		{
			for(int k = 0; k < CHUNK_Z_SIZE; k++)
			{
				for(int n = 0; n < 8; n++) // For each vector (3 floats) of our vertex array
				{
					// We copy the 3 conponents of the vector and translate them by the way
					f_vertexArray[i_vertexArraySize + 3 * n + 0] = cubeVertexArray[3 * n + 0] + i;
					f_vertexArray[i_vertexArraySize + 3 * n + 1] = cubeVertexArray[3 * n + 1] + j;
					f_vertexArray[i_vertexArraySize + 3 * n + 2] = cubeVertexArray[3 * n + 2] + k;
				}
				// We just have generated a cube vertex array, so we increase the size counter
				i_vertexArraySize += 24;

				// Now we copy an indice array with new numbers (+8 between each cube)
				for(int n = 0; n < 36; n++)
				{
					i_indiceArray[i_indiceArraySize + n] = cubeIndicesArray[n] + i_thCubeDrawed * 8;
				}
				// We take note of the new size of the indice array
				i_indiceArraySize += 36;

				//We finished to generate arrays for a cube :
				i_thCubeDrawed++;
			}
		}
	}

	// Buffer d'informations de vertex
	glBindBuffer(GL_ARRAY_BUFFER, i_bufferVertex);
	glBufferData(GL_ARRAY_BUFFER, i_vertexArraySize * sizeof(GLfloat), f_vertexArray, GL_STATIC_DRAW); // Send data
	// We finished to upload our vertex, so we can delete the temp array
	delete[] f_vertexArray;

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
	glVertexPointer( 3, // Coordinates per vertex
					 GL_FLOAT, // Data type
					 0, // Offset between each vertice
					 0 ); // where is the first vertice

	//glColorPointer( 3, GL_FLOAT, 6 * sizeof(float), 0 );

	// Activation d'utilisation des tableaux
	glEnableClientState( GL_VERTEX_ARRAY );
	//glEnableClientState( GL_COLOR_ARRAY );

	// Rendu de notre géométrie
	glDrawElements(GL_TRIANGLES, i_indiceArraySize, GL_UNSIGNED_INT, 0);

	// Désactivation des tableaux
	//glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );

	// Safely disbale buffers (for other compenents of the program)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
