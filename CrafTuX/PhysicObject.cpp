#include "PhysicObject.h"
#include <cmath> // fabs

PhysicObject::PhysicObject(preal mass) : f_mass(mass)
{
    if(f_mass == 0.0f)
    {
	f_mass = f_defaultMass;
    }
}

void PhysicObject::processMove(float f_elapsedTimeSec)
{
    // On applique l'accélération due au poids
    v3_acceleration.j -= f_g;

    // Calcul de l'accélération en fonction de la somme des forces appliquées que l'on supprime ensuite
    v3_acceleration.i += v3_forces.i / f_mass;
    v3_acceleration.j += v3_forces.j / f_mass;
    v3_acceleration.k += v3_forces.k / f_mass;

    v3_forces.null();

    v3_velocity.i += f_elapsedTimeSec*(v3_acceleration.i);
    v3_velocity.j += f_elapsedTimeSec*(v3_acceleration.j);
    v3_velocity.k += f_elapsedTimeSec*(v3_acceleration.k);

    v3_acceleration.null();

    pt_position.x += f_elapsedTimeSec*(v3_velocity.i);
    pt_position.y += f_elapsedTimeSec*(v3_velocity.j);
    pt_position.z += f_elapsedTimeSec*(v3_velocity.k);
}

void PhysicObject::applyForcev(Vector3 v3_force)
{   
    v3_forces.i += v3_force.i;
    v3_forces.j += v3_force.j;
    v3_forces.k += v3_force.k;
}
