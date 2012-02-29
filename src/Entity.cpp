#include "Entity.h"

#include <cmath>
#include <QtGlobal>
#include <QDebug>

Entity::Entity() : f_pitchDegrees(225.0f), f_yawDegrees(135.0f), b_walking(false), m_walkDirection(WalkDirection_Stop)
{
}

Vector Entity::direction()
{
	Vector v_direction;

	float r = cos(pitch() * M_PI/180.0f);
	v_direction.y = sin(pitch() * M_PI/180.0f);
	v_direction.z = r * cos(yaw() * M_PI/180.0f);
	v_direction.x = r * sin(yaw() * M_PI/180.0f);

	return v_direction;
}

void Entity::processMove(preal f_elapsedTimeSec, World& workingWorld)
{
	Vector v_walkVelocity;

	if(walking())
	{
		const preal f_walkVelocityCoefficient = 1.0e2f;
		Vector v_walkIncrement = direction() * f_walkVelocityCoefficient * f_elapsedTimeSec;

		if(m_walkDirection & WalkDirection_Forward)
		{
			v_walkVelocity += v_walkIncrement;
		}
		if(m_walkDirection & WalkDirection_Backward)
		{
			v_walkVelocity -= v_walkIncrement;
		}
		if(m_walkDirection & WalkDirection_Left)
		{
			// Mouvement latéral à droite (avec le vecteur normal à droite (-z;0;x))
			Vector leftVelocity;
			leftVelocity.x = v_walkIncrement.z;
			leftVelocity.z -= v_walkIncrement.x;
			v_walkVelocity += leftVelocity;
		}
		if(m_walkDirection & WalkDirection_Right)
		{
			// Mouvement latéral à droite (avec le vecteur normal à droite (-z;0;x))
			Vector rightVelocity;
			rightVelocity.x -= v_walkIncrement.z;
			rightVelocity.z = v_walkIncrement.x;
			v_walkVelocity += rightVelocity;
		}
	}

	v_velocity += (v_walkVelocity - v_oldWalkVelocity);
	v_oldWalkVelocity = v_walkVelocity;

	PhysicObject::processMove(f_elapsedTimeSec, workingWorld);
}

