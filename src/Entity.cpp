#include "Entity.h"
#include "FastMath.h"

#include <QDebug>

Entity::Entity(PhysicEngine* parentPhysicEngine, int id)
	: PhysicObject(parentPhysicEngine, id), f_pitchDegrees(180.0f), f_yawDegrees(135.0f), m_walkDirection(WalkDirection_Stop), b_jumping(false)
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

	const static float M_PI_OVER_180 = M_PI/180.0f;

	float r = FastMath::cos10f(pitch() * M_PI_OVER_180);
	v_direction.y = FastMath::sin10f(pitch() * M_PI_OVER_180);
	v_direction.z = r * FastMath::cos10f(yaw() * M_PI_OVER_180);
	v_direction.x = r * FastMath::sin10f(yaw() * M_PI_OVER_180);

	return v_direction;
}

void Entity::processMove(const preal f_elapsedTimeSec)
{
	v_walkVelocity *= (0.8 * f_elapsedTimeSec); // We reset/lower the walk velocity

	if(isWalking())
	{
		Vector v_direction = direction();

		if(m_walkDirection & WalkDirection_Forward)
		{
			v_walkVelocity += v_direction;
		}
		if(m_walkDirection & WalkDirection_Backward)
		{
			v_walkVelocity -= v_direction;
		}
		if(m_walkDirection & WalkDirection_Left)
		{
			// Mouvement latéral à droite (avec le vecteur normal à droite (-z;0;x))
			Vector leftVelocity;
			leftVelocity.x = v_direction.z;
			leftVelocity.z -= v_direction.x;
			v_walkVelocity += leftVelocity;
		}
		if(m_walkDirection & WalkDirection_Right)
		{
			// Mouvement latéral à droite (avec le vecteur normal à droite (-z;0;x))
			Vector rightVelocity;
			rightVelocity.x -= v_direction.z;
			rightVelocity.z = v_direction.x;
			v_walkVelocity += rightVelocity;
		}
		v_walkVelocity.y = 0.0; // In all cases, walking don't provide any vertical movement.

		v_walkVelocity.normalize();

		const preal f_walkVelocityCoefficient = 3.5;
		v_walkVelocity *= f_walkVelocityCoefficient;
	}

	if(isJumping() && touchesFloor()) // JUMP
	{
		if(v_velocity.y >= 0.0) {
			v_velocity.y = 4.35;
			v_position.y += 0.10;
		}
	}

	PhysicObject::processMove(f_elapsedTimeSec);
}

