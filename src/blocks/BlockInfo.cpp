#include "BlockInfo.h"
#include "BlockDescriptor.h"

BlockInfo* BlockInfo::voidBlock() {
	static BlockInfo voidBlock(0);
	return &voidBlock;
}
