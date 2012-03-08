#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include "Chunk.h"
#include <QThread>

class ChunkGenerator : public QThread
{
public:
	ChunkGenerator(const int seed);
	ChunkGenerator(const ChunkGenerator&);

	void run();

	inline void setChunkToGenerate(Chunk* chunkToGenerate) {m_chunkToGenerate = chunkToGenerate;}

	/*! Called in run() to generate the chunk in fact */
	void generateChunk() const;

private:
	int i_seed;
	Chunk* m_chunkToGenerate;
};

#endif // CHUNKGENERATOR_H
