#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
	Player();

	Vector eyePosition();
};

#endif // PLAYER_H
