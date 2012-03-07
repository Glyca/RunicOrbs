#ifndef CHUNK_H
#define CHUNK_H

#include <QtGlobal>
#include <QObject>
#include <QList>
#include <QPair>
#include <cmath>

#include "blocks/BlockInfo.h"
class ChunkDrawer;
class ChunkGenerator;

const int CHUNK_X_SIZE = 16;
const int CHUNK_Y_SIZE = 64;
const int CHUNK_Z_SIZE = 16;
const int CHUNK_HEIGHT = CHUNK_Y_SIZE;

class Chunk : public QObject
{
	Q_OBJECT
public:
	explicit Chunk(QObject *parent, QPair<int, int> position);
	~Chunk();

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
	QPair<int, int> m_position; //! The postion of the chunk in chunk unit.
	BlockInfo* p_BlockInfos; // pointeur vers les BlockInfo
	ChunkDrawer* m_chunkDrawer;
	ChunkGenerator* m_chunkGenerator;
};

#endif // CHUNK_H
