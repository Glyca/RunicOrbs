#ifndef VECTOR_H
#define VECTOR_H

#include "PhysicSize.h"

#include <QString>
#include <QVariant>

#include <cmath> // sqrt

/*! Fastly return a correct integer floor value, used everywhere */
inline static int ifloor(double x)
{
	return (x >= 0) ? (int)x : (int)(x - 1);
}

/*! \class Vector
	\brief A representaion of a 3D vector that holds 3 doubles and is very convenient
  */
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

	inline preal squareLength()
	{
		return (x * x + y * y + z * z);
	}

	inline preal length()
	{
		return sqrt( squareLength() );
	}

	inline void normalize()
	{
		preal length = this->length();
		x /= length;
		y /= length;
		z /= length;
	}

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
				x = - x;
				y = - y;
				z = - z;
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

	/*! Give the position of the block where vector is */
	inline void toBlock(int& bx, int& by, int& bz) const
	{
		bx = ifloor(x);
		by = ifloor(y);
		bz = ifloor(z);
	}

	preal x, y, z;
};

inline bool operator==(const Vector& v1, const Vector& v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

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
