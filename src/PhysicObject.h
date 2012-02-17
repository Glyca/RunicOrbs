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

	// Applique un vecteur force avec ces composantes en NEWTON
	void applyForcev(Vector v_force);

	void applyWeightForce();
	void applyFluidFrictionForce();

	inline preal getMass() const {return f_mass;}

public: // Public temporairement

	preal f_mass; // La masse de l'objet en KG

	Vector v_position; // La position de l'objet
	Vector v_velocity, v_acceleration; // Le vecteur vitesse et le vecteur accélération
	Vector v_forces; // Somme des forces appliquées à l'objet

public: // protected
	/*! Modifie toutes les conposantes des vecteurs et coordonnées de l'objet */
	virtual void processMove(preal f_elapsedTimeSec, World& workingWorld);
};

#endif // PHYSICOBJECT_H
