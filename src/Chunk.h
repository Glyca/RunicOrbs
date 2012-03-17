#ifndef CHUNK_H
#define CHUNK_H

#include <QtGlobal>
#include <QObject>
#include <QList>
#include <QMutex>
#include <QPair>
#include <cmath>

#include "blocks/BlockInfo.h"
class ChunkDrawer;

const int CHUNK_X_SIZE = 32;
const int CHUNK_Y_SIZE = 256;
const int CHUNK_Z_SIZE = 32;
const int CHUNK_HEIGHT = CHUNK_Y_SIZE;

class Chunk : public QObject
{
	Q_OBJECT
public:
	explicit Chunk(QObject *parent, QPair<int, int> position);
	~Chunk();

	/*! Access a block from a chunk
  \warning The coordinates to pass are relative to the chunk, and thus must be inside !
 */
	inline BlockInfo* block(const int x, const int y, const int z)
	{
		Q_ASSERT_X(fabs(x) <= CHUNK_X_SIZE  &&  fabs(z) <= CHUNK_Z_SIZE, "BlockInfo* Chunk::block(x, y, z)", "Demanded coordinates are out of the chunk!");			if(x < 0 || y < 0 || z < 0 || x >= CHUNK_X_SIZE || y >= CHUNK_Y_SIZE || z >= CHUNK_Z_SIZE)
		{
			return new BlockInfo(); // MEMORY LEAK !!!
		}
		else
		{
			int ID = y + x * CHUNK_Y_SIZE + z * CHUNK_Y_SIZE * CHUNK_X_SIZE;
			m_mutex.lock();
			BlockInfo* block = &p_BlockInfos[ID];
			m_mutex.unlock();
			return block;
		}
	}

	/*! Convert coordinates relatives to the chunk into world coordinates */
	inline void mapToWorld(const int chunkX, const int chunkY, const int chunkZ, int& worldX, int& worldY, int& worldZ) const
	{
		worldX = m_position.first * CHUNK_X_SIZE + chunkX;
		worldY = chunkY;
		worldZ = m_position.second * CHUNK_Z_SIZE + chunkZ;
	}

	//! Render all blocks of the chunk
	void render3D();

signals:

public slots:

private:
	QMutex m_mutex;
	QPair<int, int> m_position; //! The postion of the chunk in chunk unit.
	BlockInfo* p_BlockInfos; // pointeur vers les BlockInfo
	ChunkDrawer* m_chunkDrawer;
};

#endif // CHUNK_H
