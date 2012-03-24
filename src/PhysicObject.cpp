#include "PhysicObject.h"
#include "World.h"

#include <QDebug>

PhysicObject::PhysicObject(World* world, int id, preal mass) : m_world(world), f_mass(mass)
{
	if(id == 0) {
		i_id = world->server()->nextPhysicObjectId();
	}
	else {
		i_id = id;
	}

	if(f_mass == 0.0f) {
		f_mass = f_defaultMass;
	}

	v_position.y = 250;
}

PhysicObject::~PhysicObject()
{

}

Vector PhysicObject::velocity() const
{
	return v_velocity;
}

void PhysicObject::processMove(const preal f_elapsedTimeSec)
{
	// Si en dessous de nous c'est du vide, alors on applqiue le poids
	if(!this->touchesFloor()) {
		applyWeightForce();
	}
	else // Sinon on annule la vitesse verticale (collision)
	{
		v_velocity.y = 0.0;
	}

	destuck();

	applyFluidFrictionForce();

	// Calcul de l'accélération en fonction de la somme des forces appliquées que l'on supprime ensuite
	// a = F / m
	v_acceleration = v_forces / f_mass;

	// Les forces sont appliquées, donc on les supprime
	v_forces.null();

	// v += a * dt
	v_velocity += v_acceleration * f_elapsedTimeSec;

	v_totalVelocity = velocity();
	processCollisions();// corrects v_totalVelocity

	// x += v * dt
	v_position += v_totalVelocity * f_elapsedTimeSec;
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

void PhysicObject::destuck()
{
	if(isStuck()) { // If we are stuck in a non void block
		v_position.y = (preal)world()->altitude(v_position.x, v_position.z) + 0.05;
		v_velocity.null();
		v_acceleration.null();
		qDebug() << "destucked : set at" << v_position.y;
	}
}

bool PhysicObject::touchesFloor()
{
	return !world()->block((Vector(v_position.x, (v_position.y - 0.04), v_position.z)))->isVoid();
}

bool PhysicObject::isStuck()
{
	return v_position.y < (preal)world()->altitude(v_position.x, v_position.z);
}

void PhysicObject::processCollisions()
{
	const preal f_contour = 0.3;

	if(v_totalVelocity.x > 0.0
			&& ( !world()->block((Vector(v_position.x + f_contour, v_position.y, v_position.z)))->isVoid()
				 || !world()->block((Vector(v_position.x + f_contour, v_position.y + PLAYER_HEIGHT - f_contour, v_position.z)))->isVoid() ) ) {
		v_totalVelocity.x = 0.0;
	}
	else if( v_totalVelocity.x < 0.0
			 && ( !world()->block((Vector(v_position.x - f_contour, v_position.y, v_position.z)))->isVoid()
				  || !world()->block((Vector(v_position.x - f_contour, v_position.y + PLAYER_HEIGHT - f_contour, v_position.z)))->isVoid() ) ) {
		v_totalVelocity.x = 0.0;
	}

	if(v_totalVelocity.y < 0.0 && touchesFloor()) {
		v_totalVelocity.y = 0.0;
	}

	if(v_totalVelocity.z > 0.0
			&& ( !world()->block((Vector(v_position.x, v_position.y, v_position.z + f_contour)))->isVoid()
				 || !world()->block((Vector(v_position.x, v_position.y + PLAYER_HEIGHT - f_contour, v_position.z + f_contour)))->isVoid() ) ) {
		v_totalVelocity.z = 0.0;
	}
	else if(v_totalVelocity.z < 0.0
			&& ( !world()->block((Vector(v_position.x, v_position.y, v_position.z - f_contour)))->isVoid()
				 || !world()->block((Vector(v_position.x, v_position.y + PLAYER_HEIGHT - f_contour, v_position.z - f_contour)))->isVoid() ) ) {
		v_totalVelocity.z = 0.0;
	}
}
