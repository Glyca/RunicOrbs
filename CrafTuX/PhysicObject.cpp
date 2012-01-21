#include "PhysicObject.h"
#include <cmath> // fabs

PhysicObject::PhysicObject(preal mass) : f_mass(mass)
{
	if(f_mass == 0.0f)
	{
		f_mass = f_defaultMass;
	}
}

void PhysicObject::processMove(preal f_elapsedTimeSec)
{
	const preal f_h = 1e-3;

	// On applique l'accélération due au poids
	v3_forces.y -= f_g * f_mass;

	// On applique l'accélération due aux frottements fluides
	v3_forces.x -= v3_velocity.x * f_h;
	v3_forces.y -= v3_velocity.y * f_h;
	v3_forces.z -= v3_velocity.z * f_h;

	// Calcul de l'accélération en fonction de la somme des forces appliquées que l'on supprime ensuite
	// a = F / m
	v3_acceleration.x = v3_forces.x / f_mass;
	v3_acceleration.y = v3_forces.y / f_mass;
	v3_acceleration.z = v3_forces.z / f_mass;

	// Les forces sont appliquées, donc on les supprime
	v3_forces.null();

	// v += a * dt
	v3_velocity.x += v3_acceleration.x * f_elapsedTimeSec;
	v3_velocity.y += v3_acceleration.y * f_elapsedTimeSec;
	v3_velocity.z += v3_acceleration.z * f_elapsedTimeSec;

	// x += v * dt
	v3_position.x += v3_velocity.x * f_elapsedTimeSec;
	v3_position.y += v3_velocity.y * f_elapsedTimeSec;
	v3_position.z += v3_velocity.z * f_elapsedTimeSec;
}

void PhysicObject::applyForcev(Vector3 v3_force)
{   
	v3_forces.x += v3_force.x;
	v3_forces.y += v3_force.y;
	v3_forces.z += v3_force.z;
}
