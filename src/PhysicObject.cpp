#include "PhysicEngine.h"
#include "PhysicObject.h"
#include "blocks/BlockDescriptor.h"
#include "Log.h"
#include "server/Server.h"
#include "World.h"

#include <QDebug>

PhysicObject::PhysicObject(PhysicEngine* parentPhysicEngine, int id, preal mass)
	: QObject(parentPhysicEngine), m_parentPhysicEngine(parentPhysicEngine), f_mass(mass)
{
	if(id == 0) {
		i_id = world()->nextPhysicObjectId();
	}
	else {
		i_id = id;
	}

	if(f_mass == 0.0f) {
		f_mass = f_defaultMass;
	}
}

PhysicObject::~PhysicObject()
{
}

PhysicEngine* PhysicObject::physicEngine()
{
	return m_parentPhysicEngine;
}

World* PhysicObject::world()
{
	return m_parentPhysicEngine->world();
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
		v_position.y = (preal)world()->altitude(v_position.x, v_position.z) + 0.01;
		v_velocity.null();
		v_acceleration.null();
		//ldebug(Channel_Physic, "destucked : set at " + QString::number(v_position.y));
	}
}

bool PhysicObject::touchesFloor()
{
	return !world()->block((Vector(v_position.x, (v_position.y - 0.04), v_position.z)))->descriptor().canPassThrough();
}

bool PhysicObject::isStuck()
{
	return v_position.y < (preal)world()->altitude(v_position.x, v_position.z);
}

void PhysicObject::processCollisions()
{
	const preal f_contour = 0.3;

	if(v_totalVelocity.x > 0.0
			&& ( !world()->block((Vector(v_position.x + f_contour, v_position.y, v_position.z)))->descriptor().canPassThrough()
				 || !world()->block((Vector(v_position.x + f_contour, v_position.y + PLAYER_HEIGHT - f_contour, v_position.z)))->descriptor().canPassThrough() ) ) {
		v_totalVelocity.x = 0.0;
	}
	else if(v_totalVelocity.x < 0.0
			&& ( !world()->block((Vector(v_position.x - f_contour, v_position.y, v_position.z)))->descriptor().canPassThrough()
				 || !world()->block((Vector(v_position.x - f_contour, v_position.y + PLAYER_HEIGHT - f_contour, v_position.z)))->descriptor().canPassThrough() ) ) {
		v_totalVelocity.x = 0.0;
	}

	if(v_totalVelocity.y < 0.0 && touchesFloor()) {
		v_totalVelocity.y = 0.0;
	}
	else if(v_totalVelocity.y > 0.0
			&& !world()->block((Vector(v_position.x, v_position.y + PLAYER_HEIGHT + f_contour/2.0, v_position.z)))->descriptor().canPassThrough()) {
		v_totalVelocity.y = 0.0;
	}

	if(v_totalVelocity.z > 0.0
			&& ( !world()->block((Vector(v_position.x, v_position.y, v_position.z + f_contour)))->descriptor().canPassThrough()
				 || !world()->block((Vector(v_position.x, v_position.y + PLAYER_HEIGHT - f_contour, v_position.z + f_contour)))->descriptor().canPassThrough() ) ) {
		v_totalVelocity.z = 0.0;
	}
	else if(v_totalVelocity.z < 0.0
			&& ( !world()->block((Vector(v_position.x, v_position.y, v_position.z - f_contour)))->descriptor().canPassThrough()
				 || !world()->block((Vector(v_position.x, v_position.y + PLAYER_HEIGHT - f_contour, v_position.z - f_contour)))->descriptor().canPassThrough() ) ) {
		v_totalVelocity.z = 0.0;
	}
}
