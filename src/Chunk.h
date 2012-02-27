#ifndef CHUNK_H
#define CHUNK_H

#include <QtGlobal>
#include <QObject>
#include <QList>
#include <cmath>

#include "BlockInfo.h"

const int CHUNK_X_SIZE = 4;
const int CHUNK_Y_SIZE = 16;
const int CHUNK_Z_SIZE = 4;
const int CHUNK_HEIGHT = CHUNK_Y_SIZE;

class Chunk : public QObject
{
	Q_OBJECT
public:
	explicit Chunk(QObject *parent = 0);

	void generate(int seed);

	/*! Access a block from a chunk
		\warning The coordinates to pass are relative to the chunk, and thus must be inside !
	*/
	inline BlockInfo* block(const int x, const int y, const int z)
	{
		Q_ASSERT_X(fabs(x) <= CHUNK_X_SIZE  &&  fabs(z) <= CHUNK_Z_SIZE, "BlockInfo* Chunk::block(x, y, z)", "Demanded coordinates are out of the chunk!");
		// if we are over or below the chunk
		if(y > CHUNK_HEIGHT || y < 0.0)
		{
			return new BlockInfo(); // MEMORY LEAK !!!
		}
		else
		{
			int ID = y + x * CHUNK_Y_SIZE + z * CHUNK_Y_SIZE * CHUNK_X_SIZE;
			return &p_BlockInfos[ID];
		}
	}

	//! Render all blocks of the chunk
	void render3D();
	
signals:
	
public slots:

private:
	BlockInfo* p_BlockInfos; // pointeur vers les BlockInfo
};

#endif // CHUNK_H
