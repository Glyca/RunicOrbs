#include "Blocks.h"

const bool B_BREAKABLE = true, B_UNBREAKABLE = false;

namespace Blocks
{

const BlockDescriptor AIR(0, "air", B_UNBREAKABLE, QColor());
const BlockDescriptor STONE(1, "stone", B_BREAKABLE, QColor(125, 125, 125));
const BlockDescriptor DIRT(2, "dirt", B_BREAKABLE, QColor(128, 73, 58));

}
