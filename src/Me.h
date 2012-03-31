#ifndef ME_H
#define ME_H

#include "Player.h"
#include "blocks/BlockInfo.h" // BlockPosition

class Me : public Player
{
public:
	Me(World* world);

	BlockPosition pointedBlock();
	BlockPosition pointedFreeBlock();

private:

};

#endif // ME_H
