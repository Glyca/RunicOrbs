#include "Entity.h"

#include <QQuaternion>

Entity::Entity()
{
}

Vector Entity::direction()
{
	Vector v_direction;
	QQuaternion q, q_pitch, q_heading;

	// Make the Quaternions that will represent our rotations
	q_pitch.fromAxisAndAngle(1, 0, 0, f_pitchDegrees);
	q_heading.fromAxisAndAngle(0, 1, 0, f_headingDegrees);

	// Create a matrix from the pitch Quaternion and get the j vector
	// for our direction. (we don't need all the matrix, just Matrix[9])
	v_direction.y = 2.0f * ( q_pitch.y() * q_pitch.z() - q_pitch.x() * q_pitch.scalar() );

	// Combine the heading and pitch rotations and make a matrix to get
	// the i and j vectors for our direction.
	q = q_pitch * q_heading;
	v_direction.x = 2.0f * ( q.x() * q.z() + q.y() * q.scalar() );
	v_direction.z = -(  1.0f - 2.0f * ( q.x() * q.x() + q.y() * q.y() )  ); // Change by Glyca (Z axis was inverted ??)

	return v_direction;
}

