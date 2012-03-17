#ifndef ME_H
#define ME_H

#include "Player.h"

class Me : public Player
{
public:
	Me(World* world);

	Vector pointedBlock();

private:

};

#endif // ME_H
