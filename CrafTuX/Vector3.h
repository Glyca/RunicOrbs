#ifndef VECTOR3_H
#define VECTOR3_H

#include "PhysicSize.h"

class Vector3
{
public:
    Vector3(preal ni = 0, preal nj = 0, preal nk = 0) : i(ni), j(nj), k(nk) {}

    Vector3(const Vector3& other)
    {
	i = other.i;
	j = other.j;
	k = other.k;
    }

    /*inline Vector3& operator=(const Vector3& other)
    {


    }*/

    inline void null() {i = j = k = 0;}

    preal i, j, k;
};

#endif // VECTOR3_H
