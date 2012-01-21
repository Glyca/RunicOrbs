#ifndef VECTOR3_H
#define VECTOR3_H

#include "PhysicSize.h"

class Vector3
{
public:
	Vector3(preal ni = 0, preal nj = 0, preal nk = 0) : x(ni), y(nj), z(nk) {}

	Vector3(const Vector3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	inline void null() {x = y = z = 0;}

	preal x, y, z;
};

#endif // VECTOR3_H
