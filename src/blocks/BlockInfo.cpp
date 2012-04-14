#include "BlockInfo.h"

BlockInfo* BlockInfo::voidBlock() {
	static BlockInfo voidBlock(0);
	return &voidBlock;
}

