#ifndef WORLDBLOCKS_H
#define WORLDBLOCKS_H

#include "BlockInfo.h"
#include <QtGlobal> // qDebug

class WorldBlocks
{
public:
    WorldBlocks(const int WORLD_SIZE_X, const int WORLD_SIZE_Y, const int WORLD_SIZE_Z, const int SEA_LEVEL);

    // Génère le monde
    void generate(int seed);

    // Accède au pointeur sur un bloc
    inline BlockInfo* block(const int i_x, const int i_y, const int i_z)
    {
	int ID = i_y + i_x * i_SIZE_Y + i_z * i_SIZE_Y * i_SIZE_X;
	return &p_BlocksInfo[ID];
    }

private:
    int i_SIZE_X, i_SIZE_Y, i_SIZE_Z, i_SEA_LEVEL;
    BlockInfo* p_BlocksInfo; // pointeur vers les BlockInfo
};

#endif // WORLDBLOCKS_H
