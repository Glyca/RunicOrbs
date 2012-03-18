#include "Blocks.h"

const bool B_BREAKABLE = true, B_UNBREAKABLE = false;


BlockDescriptor Blocks::AIR(0, "air", B_UNBREAKABLE, QColor());
BlockDescriptor Blocks::STONE(1, "stone", B_BREAKABLE, QColor(125, 125, 125));
BlockDescriptor Blocks::DIRT(2, "dirt", B_BREAKABLE, QColor(128, 73, 58));
