#include "Chunk.h"
#include "Utils.h"

Chunk::Chunk(QObject *parent) :
	QObject(parent)
{
	int size = CHUNK_X_SIZE * CHUNK_Z_SIZE * CHUNK_Y_SIZE;
	p_BlockInfos = new BlockInfo[size];
}

void Chunk::generate(int seed)
{
	for(int j = 0; j < CHUNK_HEIGHT >> 1; j++)
	{
		for(int i = 0; i < CHUNK_X_SIZE; i++)
		{
			for(int k = 0; k < CHUNK_Z_SIZE; k++)
			{
				// On ne met que de la roche
				block(i, j, k)->setValue(1);
			}
		}
	}

	for(int j = CHUNK_HEIGHT >> 1; j < CHUNK_HEIGHT - 4; j++)
	{
		for(int i = 0; i < CHUNK_X_SIZE; i++)
		{
			for(int k = 0; k < CHUNK_Z_SIZE; k++)
			{
				// On ne met que de la terre
				block(i, j, k)->setValue(2);
			}
		}
	}
}

void Chunk::render3D()
{
	for(int j = 0; j < CHUNK_HEIGHT; j++)
	{
		for(int i = 0; i < CHUNK_X_SIZE; i++)
		{
			for(int k = 0; k < CHUNK_Z_SIZE; k++)
			{
				if(block(i, j, k)->getValue() == 1)
				{
					glColor3f(0.68f, 0.68f, 0.68f);
					glTranslatef(i, j, k);
					Utils->fastCube();
					glTranslatef(-i, -j, -k);
				}
				else if(block(i, j, k)->getValue() == 2)
				{
					glColor3f(0.488f, 0.296f, 0.078f);
					glTranslatef(i, j, k);
					Utils->fastCube();
					glTranslatef(-i, -j, -k);
				}
			}
		}
	}
}
