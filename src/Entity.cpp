#include "Entity.h"

#include <cmath>
#include <QtGlobal>
#include <QDebug>

Entity::Entity() : f_pitchDegrees(225.0f), f_headingDegrees(135.0f), b_walking(false), m_walkingDirection(WalkingDirection_Stop)
{
}

Vector Entity::direction()
{
	Vector v_direction;

	float r = cos(pitch() * M_PI/180.0f);
	v_direction.y = sin(pitch() * M_PI/180.0f);
	v_direction.z = r * cos(heading() * M_PI/180.0f);
	v_direction.x = r * sin(heading() * M_PI/180.0f);

	return v_direction;
}

void Entity::processMove(preal f_elapsedTimeSec, World& workingWorld)
{
	Vector v_walkingVelocity;

	if(walking())
	{
		const preal f_walkingVelocityCoefficient = 1.0e2f;
		Vector v_walkingIncrement = direction() * f_walkingVelocityCoefficient * f_elapsedTimeSec;

		if(m_walkingDirection & WalkingDirection_Forward)
		{
			v_walkingVelocity += v_walkingIncrement;
		}
		if(m_walkingDirection & WalkingDirection_Backward)
		{
			v_walkingVelocity -= v_walkingIncrement;
		}
		if(m_walkingDirection & WalkingDirection_Left)
		{
			// Mouvement latéral à droite (avec le vecteur normal à droite (-z;0;x))
			Vector leftVelocity;
			leftVelocity.x = v_walkingIncrement.z;
			leftVelocity.z -= v_walkingIncrement.x;
			v_walkingVelocity += leftVelocity;
		}
		if(m_walkingDirection & WalkingDirection_Right)
		{
			// Mouvement latéral à droite (avec le vecteur normal à droite (-z;0;x))
			Vector rightVelocity;
			rightVelocity.x -= v_walkingIncrement.z;
			rightVelocity.z = v_walkingIncrement.x;
			v_walkingVelocity += rightVelocity;
		}
	}

	v_velocity += (v_walkingVelocity - v_oldWalkingVelocity);
	v_oldWalkingVelocity = v_walkingVelocity;

	PhysicObject::processMove(f_elapsedTimeSec, workingWorld);
}

