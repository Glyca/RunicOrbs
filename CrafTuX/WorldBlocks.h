#ifndef WORLDBLOCKS_H
#define WORLDBLOCKS_H

#include "BlockInfo.h"
#include "PhysicSize.h"
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
		if(i_x <= i_SIZE_X && i_y <= i_SIZE_Y && i_z <= i_SIZE_Z) {
			int ID = i_y + i_x * i_SIZE_Y + i_z * i_SIZE_Y * i_SIZE_X;
			return &p_BlocksInfo[ID];
		} else {
			return BlockInfo::voidBlock();
		}
	}

	BlockInfo* blockBelow(preal f_x, preal f_y, preal f_z);

	inline int getSizeX(void) {
		return i_SIZE_X;
	}

	inline int getSizeY(void) {
		return i_SIZE_Y;
	}

	inline int getSizeZ(void) {
		return i_SIZE_Z;
	}

	static void prealToInt(preal f_x, preal f_y, preal f_z, int& i_x, int& i_y, int& i_z);

private:
	int i_SIZE_X, i_SIZE_Y, i_SIZE_Z, i_SEA_LEVEL;
	BlockInfo* p_BlocksInfo; // pointeur vers les BlockInfo
};

#endif // WORLDBLOCKS_H
