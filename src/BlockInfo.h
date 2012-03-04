#ifndef BLOCKINFO_H
#define BLOCKINFO_H

class BlockInfo
{
public:
	BlockInfo(int value = 0);

	// Retourne un bloc vide
	static BlockInfo* voidBlock();

	// L'ID DU BLOCK (SON TYPE)
	int id() const;
	void setId(const int value);

	// SI LE BLOC EST ELECTRIFIE
	bool isPowered() const;
	void makePowered(const bool yes);

private:

	unsigned short int i_value;
	bool b_isPowered;

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
