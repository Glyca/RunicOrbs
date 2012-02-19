#ifndef CHUNK_H
#define CHUNK_H

#include <QtGlobal>
#include <QObject>
#include <QList>

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
		Q_ASSERT_X(x <= CHUNK_X_SIZE && y <= CHUNK_Y_SIZE && z <= CHUNK_Z_SIZE, "BlockInfo* Chunk::block(x, y, z)", "Demanded coordinates are out of the chunk!");
		int ID = y + x * CHUNK_Y_SIZE + z * CHUNK_Y_SIZE * CHUNK_X_SIZE;
		return &p_BlockInfos[ID];
	}

	//! It is not a real hash ! It's juste to make a diffence between two chunk loaded into memory for operator==.
	inline BlockInfo* hash() const {return p_BlockInfos;}
	
signals:
	
public slots:

private:
	BlockInfo* p_BlockInfos; // pointeur vers les BlockInfo
};

inline bool operator==(const Chunk &chunk1, const Chunk& chunk2)
{
	return chunk1.hash() == chunk2.hash();
}

#endif // CHUNK_H
