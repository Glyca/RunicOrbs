#ifndef WORLDBLOCKS_H
#define WORLDBLOCKS_H

#include "BlockInfo.h"

class WorldBlocks
{
public:
    WorldBlocks(const int WORLD_SIZE_X, const int WORLD_SIZE_Y, const int WORLD_SIZE_Z, const int SEA_LEVEL);

    void generate(int seed);

    inline BlockInfo* block(const int i_x, const int i_y, const int i_z)
    {
	return &p_BlocksInfo[i_y * i_SIZE_Y * i_SIZE_X + i_x * i_SIZE_X + i_z];
    }

private:
    int i_SIZE_X, i_SIZE_Y, i_SIZE_Z, i_SEA_LEVEL;
    BlockInfo* p_BlocksInfo; // pinteur vers des pointeurs de Blockinfo
};

#endif // WORLDBLOCKS_H
