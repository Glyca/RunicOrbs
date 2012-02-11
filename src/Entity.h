#ifndef ENTITY_H
#define ENTITY_H

#include "PhysicObject.h"

class Entity : public PhysicObject
{
public:
	Entity();

	/*! The direction the entity is looking at */
	Vector direction();
	inline qreal pitch() const {return f_pitchDegrees;}
	inline qreal heading() const {return f_headingDegrees;}

	/*! Make the Entity walk to the direction direction */
	inline void walk(Vector direction) {v_walkingDirection = direction; b_walking = true;}
	/*! Stop the Entity walking */
	inline void stopWalk() {b_walking = false;}
	/*! Wether the Entity is walking or not */
	inline bool walking() const {return b_walking;}

protected:
	void processMove(preal f_elapsedTimeSec);

private:
	qreal f_pitchDegrees, f_headingDegrees;
	bool b_walking;
	Vector v_walkingDirection;
};

#endif // ENTITY_H
