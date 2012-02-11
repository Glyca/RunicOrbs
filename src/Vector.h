#ifndef VECTOR_H
#define VECTOR_H

#include "PhysicSize.h"

#include <QString>
#include <QVariant>

class Vector
{
public:
	Vector(preal ni = 0.0, preal nj = 0.0, preal nk = 0.0) : x(ni), y(nj), z(nk) {}

	Vector(const Vector& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	inline void null() {x = y = z = 0.0;}

	// Operators between Vectors

	inline Vector& operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	inline Vector& operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	inline Vector& operator-()
	{
		x -= x;
		y -= y;
		z -= z;
		return *this;
	}

	// Operators between Vectors and preals

	inline Vector& operator*=(const preal real)
	{
		x *= real;
		y *= real;
		z *= real;
		return *this;
	}

	inline Vector& operator/=(const preal real)
	{
		x /= real;
		y /= real;
		z /= real;
		return *this;
	}

	// Useful

	inline operator QString()
	{
		return QString("(" + QVariant(x).toString() + "; " + QVariant(y).toString() + "; " + QVariant(z).toString() + ")");
	}

	preal x, y, z;
};

inline Vector operator+(const Vector& v1, const Vector& v2)
{
	Vector sum(v1);
	sum += v2;
	return sum;
}

inline Vector operator-(const Vector& v1, const Vector& v2)
{
	Vector diff(v1);
	diff -= v2;
	return diff;
}

inline Vector operator*(const Vector& v, const preal real)
{
	Vector result(v);
	result *= real;
	return result;
}

inline Vector operator/(const Vector& v, const preal real)
{
	Vector result(v);
	result /= real;
	return result;
}

#endif // VECTOR_H
