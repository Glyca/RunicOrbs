#ifndef BLOCKINFO_H
#define BLOCKINFO_H

#include <QString>
#include <QVariant>

#include "Blocks.h"

const int DEFAULT_BLOCK_ID = 0;

/*! A block of a Chunk with its current id, lighting... */
class BlockInfo
{
public:
	BlockInfo(int value = DEFAULT_BLOCK_ID) : i_value(value) {}

	// Retourne un bloc vide
	static BlockInfo* voidBlock();

	/*! Return the ID of the block */
	int id() const { return i_value; }
	void setId(const int value) { i_value = value; }

	inline bool isVoid() { return (id() == 0); }

	inline int lightLevel() const {return i_lightLevel;}

	inline BlockDescriptor& descriptor() { return Blocks::byId(id()); }

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

/*! 3 integers representating a block position in the world */
class BlockPosition {
public:
	BlockPosition(int i = 0, int j = 0, int k = 0) : x(i), y(j), z(k) {}
	inline operator QString() {
		return QString("(" + QVariant(x).toString() + "; " + QVariant(y).toString() + "; " + QVariant(z).toString() + ")");
	}
	int x, y, z;
};

#endif // BLOCKINFO_H
