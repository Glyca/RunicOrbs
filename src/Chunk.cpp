#include "Chunk.h"

Chunk::Chunk(QObject *parent) :
	QObject(parent)
{
	int size = CHUNK_X_SIZE * CHUNK_Z_SIZE * CHUNK_Y_SIZE;
	p_BlockInfos = new BlockInfo[size];
}

void Chunk::generate(int seed)
{
	qDebug("Génération d'un chunk...");

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
	qDebug("Poids brut total du chunk : %ld Kio", (CHUNK_X_SIZE * CHUNK_Y_SIZE * CHUNK_Z_SIZE * sizeof(BlockInfo)) >> 10);
}
