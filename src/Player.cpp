#include "Player.h"

Player::Player()
{
}

Vector Player::eyePosition()
{
	Vector footPosition = v_position;
	footPosition.y += 1.65; // not 1.75 because eyes are a little bit under
	return footPosition;
}
