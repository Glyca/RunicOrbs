#ifndef PHYSICOBJECT_H
#define PHYSICOBJECT_H

#include <QObject>
#include <QElapsedTimer>
#include "PhysicSize.h"
#include "Vector.h"

class PhysicEngine;
class World;

/*! An object on which physic can be applied in a PhysicEngine */
class PhysicObject : public QObject
{
	friend class PhysicEngine;
public:
	PhysicObject(PhysicEngine* parentPhysicEngine, int id = 0, preal mass = f_defaultMass);
	virtual ~PhysicObject();

	PhysicEngine* physicEngine();
	inline int id() const {return i_id;}
	World* world();

	virtual Vector velocity() const;

	// Applique un vecteur force avec ces composantes en NEWTON
	void applyForcev(const Vector& v_force);

	void applyWeightForce();
	void applyFluidFrictionForce();

	/*! Unstuck a PhysicObject in the floor (may be caused by low FPS */
	void destuck();

	preal mass() const {return f_mass;}
	void setMass(preal mass) {f_mass = mass;}

	/*! Wether the object is lying on the floor or not */
	bool touchesFloor();
	/*! Wether the object is stuck */
	bool isStuck();

public: // Public temporairement

	Vector v_position; // La position de l'objet
	Vector v_velocity, v_totalVelocity, v_acceleration; // Le vecteur vitesse et le vecteur accélération
	Vector v_forces; // Somme des forces appliquées à l'objet

protected: // protected
	/*! Modifie toutes les conposantes des vecteurs et coordonnées de l'objet */
	virtual void processMove(const preal f_elapsedTimeSec);

	void processCollisions();

private:
	PhysicEngine* m_parentPhysicEngine;
	int i_id; //!< The ID of the PhysicObject on this server
	preal f_mass; //!< The mass of the object in kg
};

#endif // PHYSICOBJECT_H
