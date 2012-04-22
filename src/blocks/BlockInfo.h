#ifndef BLOCKINFO_H
#define BLOCKINFO_H

#include <QString>

#include "Blocks.h"

/*! 3 integers representating a block position in the world */
struct BlockPosition {
	BlockPosition(int i = 0, int j = 0, int k = 0) : x(i), y(j), z(k) {}
	inline operator QString() const {
		return QString("(" + QString::number(x) + "; " + QString::number(y) + "; " + QString::number(z) + ")");
	}
	int x, y, z;
};

const int DEFAULT_BLOCK_ID = 0;

/*! A block of a Chunk with its current id, lighting... */
class BlockInfo
{
public:
	BlockInfo(int value = DEFAULT_BLOCK_ID) : i_value(value), i_lightLevel(0), b_powered(false) {}

	// Retourne un bloc vide
	static BlockInfo* voidBlock();

	/*! Return the ID of the block */
	int id() const { return i_value; }
	void setId(const int value) { i_value = value; }

	inline bool isVoid() const { return (id() == 0); }

	inline int lightLevel() const {return i_lightLevel;}
	inline void setLightLevel(const int lightLevel) {i_lightLevel = lightLevel;}

	inline BlockDescriptor& descriptor() const { return Blocks::byId(id()); }

private:
	unsigned int	i_value		: 12; // 4096 blocks possible.
	unsigned int	i_lightLevel: 4;
	bool			b_powered	: 1; //!< Whether the block is under electrically powered or not
	int				i_unused	: 15;
};

inline bool operator==(const BlockInfo& block1, const BlockInfo& block2)
{
	return (block1.id() == block2.id());
}

inline bool operator!=(const BlockInfo& block1, const BlockInfo& block2)
{
	return !(block1 == block2);
}

/*! Contains the BlockInfo of a block, its BlockPosition and many pointers to surrounding blocks.
It is used in block drawing to avoid the fetch of all surrounding blocks for each block.
Instead there is just some swaps between these BlockInfo pointers and fetchs of only non-already-fetched blocks. */
struct BlockSet
{
	BlockInfo* block;
	BlockPosition* position;

	BlockInfo* frontBlock;
	BlockInfo* leftBlock;
	BlockInfo* bottomBlock;
	BlockInfo* rightBlock;
	BlockInfo* topBlock;
	BlockInfo* backBlock;

	BlockInfo* topFrontBlock;
	BlockInfo* topLeftBlock;
	BlockInfo* topRightBlock;
	BlockInfo* topBackBlock;

	BlockInfo* topFrontLeftBlock;
	BlockInfo* topFrontRightBlock;
	BlockInfo* topBackLeftBlock;
	BlockInfo* topBackRightBlock;
};

#endif // BLOCKINFO_H
