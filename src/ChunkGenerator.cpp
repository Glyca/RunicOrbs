#include "ChunkGenerator.h"
#include "PNoise.h"

ChunkGenerator::ChunkGenerator(Chunk* chunkToGenerate, int seed) : m_chunkToGenerate(chunkToGenerate), i_seed(seed)
{

}

void ChunkGenerator::generateChunk()
{
	PNoise* noise = new PNoise(i_seed);
	for(int j = 0; j < CHUNK_HEIGHT; j++)
	{
		for(int i = 0; i < CHUNK_X_SIZE; i++)
		{
			for(int k = 0; k < CHUNK_Z_SIZE; k++)
			{
				int wi, wj, wk; // Coordinates in the world
				m_chunkToGenerate->mapToWorld(i, j, k, wi, wj, wk);
				double perlin = noise->PerlinNoise3D(wi+0.5, wj+0.5, wk+0.5, 2, CHUNK_HEIGHT);

				if(perlin > 0.2)
				{
					m_chunkToGenerate->block(i, j, k)->setId(1);
				}
				else if(perlin >= 0)
				{
					m_chunkToGenerate->block(i, j, k)->setId(2);
				}
			}
		}
	}
	delete noise;
}
