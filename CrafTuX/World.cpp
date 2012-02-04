#include <cmath> // floor

#include "World.h"

World::World(QObject *parent) :
	QObject(parent)
{
}

void World::vector2int(Vector& vector, int& ix, int& iy, int& iz)
{
	ix = floor(vector.x);
	iy = floor(vector.y);
	iz = floor(vector.z);
}
