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
	const preal f_walkingForce = 10.0f;
	if(walking())
	{
		Vector v_walkingForce = direction() * f_walkingForce * f_elapsedTimeSec;
		if(m_walkingDirection & WalkingDirection_Forward)
		{
			applyForcev(v_walkingForce);
		}
		if(m_walkingDirection & WalkingDirection_Backward)
		{
			Vector backwardForce; backwardForce -= v_walkingForce;
			applyForcev(backwardForce);
		}
		if(m_walkingDirection & WalkingDirection_Left)
		{
			// Mouvement latéral à droite (avec le vecteur normal à droite (-z;0;x))
			Vector leftForce;
			leftForce.x = v_walkingForce.z;
			leftForce.z -= v_walkingForce.x;
			applyForcev(leftForce);
		}
		if(m_walkingDirection & WalkingDirection_Right)
		{
			// Mouvement latéral à droite (avec le vecteur normal à droite (-z;0;x))
			Vector rightForce;
			rightForce.x -= v_walkingForce.z;
			rightForce.z = v_walkingForce.x;
			applyForcev(rightForce);
		}
	}

	PhysicObject::processMove(f_elapsedTimeSec, workingWorld);
}

