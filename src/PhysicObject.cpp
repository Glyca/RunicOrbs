#include "PhysicObject.h"
#include "World.h"

#include <QDebug>

PhysicObject::PhysicObject(preal mass) : f_mass(mass)
{
	if(f_mass == 0.0f)
	{
		f_mass = f_defaultMass;
	}

	v_position.y = 50;
}

void PhysicObject::processMove(preal f_elapsedTimeSec, World &workingWorld)
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

	processCollisions(workingWorld);

	// x += v * dt
	v_position += v_velocity * f_elapsedTimeSec;
}

void PhysicObject::applyForcev(Vector v_force)
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
	v_forces -= v_velocity * f_h;
}

bool PhysicObject::touchesFloor(World &workingWorld)
{
	return !workingWorld.block((Vector(v_position.x, (v_position.y - 0.2), v_position.z)))->isVoid();
}

void PhysicObject::processCollisions(World& workingWorld)
{
	const preal f_contour = 0.2;

	if(v_velocity.x > 0 && !workingWorld.block((Vector(v_position.x + f_contour, v_position.y, v_position.z)))->isVoid())
	{
		v_velocity.x = 0;
	}
	else if(v_velocity.x < 0 && !workingWorld.block((Vector(v_position.x - f_contour, v_position.y, v_position.z)))->isVoid())
	{
		v_velocity.x = 0;
	}

	if(v_velocity.y < 0 && !workingWorld.block((Vector(v_position.x, v_position.y - f_contour, v_position.z)))->isVoid())
	{
		v_velocity.y = 0;
	}

	if(v_velocity.z > 0 && !workingWorld.block((Vector(v_position.x, v_position.y, v_position.z + f_contour)))->isVoid())
	{
		v_velocity.z = 0;
	}
	else if(v_velocity.z < 0 && !workingWorld.block((Vector(v_position.x, v_position.y, v_position.z - f_contour)))->isVoid())
	{
		v_velocity.z = 0;
	}
}
