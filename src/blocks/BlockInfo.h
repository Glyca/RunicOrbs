#ifndef BLOCKINFO_H
#define BLOCKINFO_H

const int DEFAULT_BLOCK_ID = 0;

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

private:
	unsigned int	i_value		: 12; // 4096 blocks possible.
	bool			b_powered	: 1;
};

inline bool operator==(const BlockInfo& block1, const BlockInfo& block2)
{
	return (block1.id() == block2.id());
}

inline bool operator!=(const BlockInfo& block1, const BlockInfo& block2)
{
	return !(block1 == block2);
}

extern BlockInfo AIR;
extern BlockInfo STONE;
extern BlockInfo DIRT;

#endif // BLOCKINFO_H
