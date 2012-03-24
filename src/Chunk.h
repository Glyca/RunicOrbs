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

const int CHUNK_X_SIZE = 24;
const int CHUNK_Y_SIZE = 256;
const int CHUNK_Z_SIZE = 24;
const int CHUNK_HEIGHT = CHUNK_Y_SIZE;

typedef QPair<int, int> ChunkPostition;

class Chunk : public QObject
{
public:
	explicit Chunk(QObject *parent, ChunkPostition position);
	~Chunk();

	enum ChunkState {
		ChunkState_Active,
		ChunkState_Idle,
		ChunkState_Void
	};

	void activate(); //! Activate the chunk (it will be drawed)
	void idle(); //! Make the Chunk enter in an idle state (it will not be drawed)

	inline ChunkPostition position() const {return m_position;}
	int altitude(const int x, const int z);

	/*! Access a block from a chunk
  \warning The coordinates to pass are relative to the chunk, and thus must be inside !
 */
	inline BlockInfo* block(const int x, const int y, const int z)
	{
		if(x < 0 || y < 0 || z < 0 || x >= CHUNK_X_SIZE || y >= CHUNK_Y_SIZE || z >= CHUNK_Z_SIZE) {
			return BlockInfo::voidBlock();
		}
		else {
			int ID = y + x * CHUNK_Y_SIZE + z * CHUNK_Y_SIZE * CHUNK_X_SIZE;
			BlockInfo* block = &p_BlockInfos[ID];
			return block;
		}
	}

	/*! Convert coordinates relatives to the chunk into world coordinates */
	void mapToWorld(const int chunkX, const int chunkY, const int chunkZ, int& worldX, int& worldY, int& worldZ) const;

	/*! This will force the chunk to be redrawed */
	inline void makeDirty() {b_dirty = true;}

	//! Render all blocks of the chunk
	void render3D();

signals:

public slots:

private:
	ChunkState m_state;
	bool b_dirty; //! If we need to redraw the chunk
	ChunkPostition m_position; //! The postion of the chunk in chunk unit.
	BlockInfo* p_BlockInfos; //! A big array of all BlockInfo of the Chunk
	ChunkDrawer* m_chunkDrawer;
};

#endif // CHUNK_H
