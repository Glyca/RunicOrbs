#include "Me.h"
#include "World.h"

/*! How much do we increase the direction vector to see if there is a cube */
const float F_BLOCK_SEAK_STEP = 0.05f;

/*! How far do we loook for a non-void cube */
const float F_MAX_BLOCK_SEAK = 8.0f;

Me::Me(World* world)
{
	setMass(70.0f); // 70kg is good
	m_world = world;
	qDebug("Me created");
}

BlockPosition Me::pointedBlock()
{
	BlockPosition blockPosition;
	Vector direction = this->direction();
	Vector position = this->eyePosition();
	for(float d = 1; d < F_MAX_BLOCK_SEAK; d += F_BLOCK_SEAK_STEP)
	{
		blockPosition.x = ifloor(position.x + direction.x * d);
		blockPosition.y = ifloor(position.y + direction.y * d);
		blockPosition.z = ifloor(position.z + direction.z * d);

		if(!world()->block(blockPosition)->isVoid()) {
			return blockPosition;
		}
	}
	return BlockPosition(); // return 0,0,0
}

BlockPosition Me::pointedFreeBlock()
{
	BlockPosition blockPosition, lastBlockPosition;
	Vector direction = this->direction();
	Vector position = this->eyePosition();
	for(float d = 1; d < F_MAX_BLOCK_SEAK; d += F_BLOCK_SEAK_STEP)
	{
		lastBlockPosition = blockPosition;

		blockPosition.x = ifloor(position.x + direction.x * d);
		blockPosition.y = ifloor(position.y + direction.y * d);
		blockPosition.z = ifloor(position.z + direction.z * d);

		// If we met a non void block...
		if(!world()->block(blockPosition)->isVoid()) {
			return lastBlockPosition; // We return the last void block
		}
	}
	return BlockPosition(); // return 0,0,0
}

