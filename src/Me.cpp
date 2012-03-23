#include "Me.h"
#include "World.h"

/*! How much do we increase the direction vector to see if there is a cube */
const float F_BLOCK_SEAK_STEP = 0.05f;

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
	for(float d = 1; d < 50.0f; d += F_BLOCK_SEAK_STEP)
	{
		blockPosition.x = ifloor(v_position.x + (direction.x)*d);
		blockPosition.y = ifloor(v_position.y + (direction.y)*d + 1);
		blockPosition.z = ifloor(v_position.z + (direction.z)*d);

		if(!world()->block(blockPosition)->isVoid())
		{
			return blockPosition;
		}
	}
	return blockPosition;
}

BlockPosition Me::pointedFreeBlock()
{
	BlockPosition blockPosition, lastBlockPosition;
	Vector direction = this->direction();
	for(float d = 1; d < 50.0f; d += F_BLOCK_SEAK_STEP)
	{
		lastBlockPosition = blockPosition;

		blockPosition.x = ifloor(v_position.x + (direction.x)*d);
		blockPosition.y = ifloor(v_position.y + (direction.y)*d + 1);
		blockPosition.z = ifloor(v_position.z + (direction.z)*d);

		// If we met a non void block...
		if(!world()->block(blockPosition)->isVoid())
		{
			return lastBlockPosition; // We return the last void block
		}
	}
	return blockPosition;
}

