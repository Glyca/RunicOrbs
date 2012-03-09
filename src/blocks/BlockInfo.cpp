#include "BlockInfo.h"

BlockInfo* BlockInfo::voidBlock() {
	BlockInfo* voidBlock = new BlockInfo(0);
	return voidBlock;
}

