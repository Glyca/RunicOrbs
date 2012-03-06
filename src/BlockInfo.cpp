#include "BlockInfo.h"

BlockInfo AIR(0);
BlockInfo STONE(1);
BlockInfo DIRT(2);

BlockInfo::BlockInfo(int value) : i_value(value)
{
}

BlockInfo* BlockInfo::voidBlock() {
	BlockInfo* voidBlock = new BlockInfo();
	return voidBlock;
}

int BlockInfo::id() const
{
	return i_value;
}

void BlockInfo::setId(const int value)
{
	i_value = value;
}

