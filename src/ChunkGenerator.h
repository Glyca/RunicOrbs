#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include "Chunk.h"
#include <QThread>

class ChunkGenerator : public QThread
{
public:
	ChunkGenerator(const int seed);
	ChunkGenerator(const ChunkGenerator&);

	/*! Called to generate the chunk in fact */
	void run();

	inline void setChunkToGenerate(Chunk* chunkToGenerate) {m_chunkToGenerate = chunkToGenerate;}

private:
	int i_seed;
	Chunk* m_chunkToGenerate;
	static double noise(const double xin, const double yin, const double zin);
};

#endif // CHUNKGENERATOR_H
