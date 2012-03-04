#include "BlockInfo.h"
#include <QtGlobal>

BlockInfo::BlockInfo(int value) : i_value(value)
{
	makePowered(true);
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

bool BlockInfo::isPowered() const
{
	return b_isPowered;
}

void BlockInfo::makePowered(const bool yes)
{
	b_isPowered = yes;
}


