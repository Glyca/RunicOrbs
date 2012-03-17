#include "PhysicObject.h"
#include "World.h"

#include <QDebug>

PhysicObject::PhysicObject(World* world, preal mass) : m_world(world), f_mass(mass)
{
	if(f_mass == 0.0f)
	{
		f_mass = f_defaultMass;
	}

	v_position.y = 50;
}

PhysicObject::~PhysicObject()
{

}

Vector PhysicObject::velocity() const
{
	return v_velocity;
}

void PhysicObject::processMove(const preal f_elapsedTimeSec, World& workingWorld)
{
	// Si en dessous de nous c'est du vide, alors on applqiue le poids
	if(!this->touchesFloor(workingWorld)) {
		applyWeightForce();
	}
	else // Sinon on annule la vitesse verticale (collision)
	{
		v_velocity.y = 0.0;
	}

	applyFluidFrictionForce();

	// Calcul de l'accélération en fonction de la somme des forces appliquées que l'on supprime ensuite
	// a = F / m
	v_acceleration = v_forces / f_mass;

	// Les forces sont appliquées, donc on les supprime
	v_forces.null();

	// v += a * dt
	v_velocity += v_acceleration * f_elapsedTimeSec;

	v_tempVelocity = velocity();
	processCollisions(workingWorld);// corrects v_tempVelocity

	// x += v * dt
	v_position += v_tempVelocity * f_elapsedTimeSec;
}

void PhysicObject::applyForcev(const Vector& v_force)
{
	v_forces += v_force;
}

void PhysicObject::applyWeightForce()
{
	v_forces.y -= f_g * f_mass;
}

void PhysicObject::applyFluidFrictionForce()
{
	// On applique l'accélération due aux frottements fluides
	const preal f_h = 1e-3;
	v_forces -= velocity() * f_h;
}

bool PhysicObject::touchesFloor(World& workingWorld)
{
	return !workingWorld.block((Vector(v_position.x, (v_position.y - 1), v_position.z)))->isVoid();
}

void PhysicObject::processCollisions(World& workingWorld)
{
	const preal f_contour = 0.1;

	if(v_tempVelocity.x > 0.0 && !workingWorld.block((Vector(v_position.x + f_contour, v_position.y, v_position.z)))->isVoid())
	{
		v_tempVelocity.x = 0.0;
	}
	else if(v_tempVelocity.x < 0.0 && !workingWorld.block((Vector(v_position.x - f_contour, v_position.y, v_position.z)))->isVoid())
	{
		v_tempVelocity.x = 0.0;
	}

	if(v_tempVelocity.y < 0.0 && !workingWorld.block((Vector(v_position.x, v_position.y - f_contour, v_position.z)))->isVoid())
	{
		v_tempVelocity.y = 0.0;
	}

	if(v_tempVelocity.z > 0.0 && !workingWorld.block((Vector(v_position.x, v_position.y, v_position.z + f_contour)))->isVoid())
	{
		v_tempVelocity.z = 0.0;
	}
	else if(v_tempVelocity.z < 0.0 && !workingWorld.block((Vector(v_position.x, v_position.y, v_position.z - f_contour)))->isVoid())
	{
		v_tempVelocity.z = 0.0;
	}
}
