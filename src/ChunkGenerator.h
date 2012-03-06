#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include "Chunk.h"

class ChunkGenerator
{
public:
	ChunkGenerator(Chunk* chunkToGenerate, int seed);

	void generateChunk();

private:
	int i_seed;
	Chunk* m_chunkToGenerate;

	static double noise(double xin, double yin);
	static double noise(double xin, double yin, double zin);
};

#endif // CHUNKGENERATOR_H
