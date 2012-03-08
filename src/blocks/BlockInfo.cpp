#include "BlockInfo.h"

BlockInfo AIR(0);
BlockInfo STONE(1);
BlockInfo DIRT(2);

BlockInfo* BlockInfo::voidBlock() {
	BlockInfo* voidBlock = new BlockInfo(0);
	return voidBlock;
}

