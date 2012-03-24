#include "Entity.h"

#include <cmath>
#include <QtGlobal>
#include <QDebug>

Entity::Entity(int id) : PhysicObject(world(), id), f_pitchDegrees(180.0f), f_yawDegrees(135.0f), m_walkDirection(WalkDirection_Stop), b_jumping(false)
{
}

Entity::~Entity()
{

}

Vector Entity::velocity() const
{
	return (v_walkVelocity + PhysicObject::velocity());
}

Vector Entity::direction() const
{
	Vector v_direction;

	float r = cos(pitch() * M_PI/180.0f);
	v_direction.y = sin(pitch() * M_PI/180.0f);
	v_direction.z = r * cos(yaw() * M_PI/180.0f);
	v_direction.x = r * sin(yaw() * M_PI/180.0f);

	return v_direction;
}

void Entity::processMove(const preal f_elapsedTimeSec, World& workingWorld)
{
	v_walkVelocity.null(); // We reset the walk velocity

	if(isWalking())
	{
		const preal f_walkVelocityCoefficient = 5.0f;
		Vector v_walkIncrement = direction() * f_walkVelocityCoefficient;

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
		v_walkVelocity.y = 0.0; // In all cases, walking don't provide any vertical movement.
	}

	if(isJumping() && this->touchesFloor())
	{
		const preal f_jumpVerticalForce = 350.0; // NEWTONS
		applyForcev(Vector(0.0, f_jumpVerticalForce / f_elapsedTimeSec, 0.0)); // Jump force is thus not proportional to the delta of time, since it's a force
	}

	PhysicObject::processMove(f_elapsedTimeSec, workingWorld);
}

