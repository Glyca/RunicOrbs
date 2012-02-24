#include "Entity.h"

#include <cmath>
#include <QtGlobal>
#include <QQuaternion>
#include <QDebug>

Entity::Entity() : f_pitchDegrees(225.0f), f_headingDegrees(135.0f), b_walking(false), m_walkingDirection(WalkingDirection_Stop)
{
}

Vector Entity::direction()
{
	Vector v_direction;

	double r = cos(pitch() * M_PI/180);
	v_direction.y = sin(pitch() * M_PI/180.0);
	v_direction.z = r * cos(heading() * M_PI/180.0);
	v_direction.x = r * sin(heading() * M_PI/180.0);

	return v_direction;
}

void Entity::processMove(preal f_elapsedTimeSec, World& workingWorld)
{
	const preal f_walkingVelocity = 5.0f;
	if(walking())
	{
		if(m_walkingDirection & WalkingDirection_Forward)
		{
			v_position += direction() * f_walkingVelocity * f_elapsedTimeSec;
		}
		if(m_walkingDirection & WalkingDirection_Backward)
		{
			v_position -= direction() * f_walkingVelocity * f_elapsedTimeSec;
		}
		if(m_walkingDirection & WalkingDirection_Left)
		{
			// Mouvement latéral à droite (avec le vecteur normal à droite (-z;0;x))
			v_position.x += direction().z * f_walkingVelocity * f_elapsedTimeSec;
			v_position.z -= direction().x * f_walkingVelocity * f_elapsedTimeSec;
		}
		if(m_walkingDirection & WalkingDirection_Right)
		{
			// Mouvement latéral à droite (avec le vecteur normal à droite (-z;0;x))
			v_position.x -= direction().z * f_walkingVelocity * f_elapsedTimeSec;
			v_position.z += direction().x * f_walkingVelocity * f_elapsedTimeSec;
		}
	}

	PhysicObject::processMove(f_elapsedTimeSec, workingWorld);
}

