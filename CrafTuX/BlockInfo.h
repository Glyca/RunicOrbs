#ifndef BLOCKINFO_H
#define BLOCKINFO_H

const int SIZE_OF_A_INT_TIMES_8 = sizeof(int)*8;

const int VALUE_BITS_SHIFT = 0;
const int VALUE_BITS_SIZE = 10;
const int POWERED_BITS_SHIFT = 10;
const int POWERED_BITS_SIZE = 1;

class BlockInfo
{
public:
    BlockInfo(int value = 0);

	// Retourne un bloc vide
	static BlockInfo* voidBlock();

    // L'ID DU BLOCK (SON TYPE)
    int getValue() const;
    void setValue(const int value);

    // SI LE BLOC EST ELECTRIFIE
    bool isPowered() const;
    void makePowered(const bool yes);

private:

	unsigned short int i_value;
    bool b_isPowered;

    inline int readShiftMaskBits(const int source, const int shift, const int size) const
    {
	return (( (source << shift) << (SIZE_OF_A_INT_TIMES_8 - size) ) >> size);
    }



};

#endif // BLOCKINFO_H
