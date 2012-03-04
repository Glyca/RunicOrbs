#include "PhysicObject.h"
#include "World.h"

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
	return !(0 == workingWorld.block((Vector(v_position.x, (v_position.y + 0.1), v_position.z)))->id());
}
