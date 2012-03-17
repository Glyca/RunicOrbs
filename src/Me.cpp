#include "Me.h"
#include "World.h"

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
	for(int d = 1; d < 50; d++)
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
