#ifndef PHYSICOBJECT_H
#define PHYSICOBJECT_H

#include <QObject>
#include <QElapsedTimer>
#include "PhysicSize.h"
#include "Vector.h"

class PhysicEngine;
class World;

class PhysicObject : public QObject
{
	Q_OBJECT
	friend class PhysicEngine;
public:
	PhysicObject(preal mass = f_defaultMass);
	virtual ~PhysicObject();

	// Applique un vecteur force avec ces composantes en NEWTON
	void applyForcev(Vector v_force);

	void applyWeightForce();
	void applyFluidFrictionForce();

	inline preal mass() const {return f_mass;}
	inline void setMass(const preal mass) {f_mass = mass;}

	/*! Wether the object is lying on the floor or not */
	bool touchesFloor(World& workingWorld);



public: // Public temporairement

	Vector v_position; // La position de l'objet
	Vector v_velocity, v_acceleration; // Le vecteur vitesse et le vecteur accélération
	Vector v_forces; // Somme des forces appliquées à l'objet

protected: // protected
	/*! Modifie toutes les conposantes des vecteurs et coordonnées de l'objet */
	virtual void processMove(preal f_elapsedTimeSec, World& workingWorld);

	void processCollisions(World& workingWorld);

	preal f_mass; // La masse de l'objet en KG
};

#endif // PHYSICOBJECT_H
