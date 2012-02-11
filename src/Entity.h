#ifndef ENTITY_H
#define ENTITY_H

#include "PhysicObject.h"

class Entity : public PhysicObject
{
public:
	Entity();

	// *! The direction the entity is looking at
	Vector direction();
	inline qreal pitch() const {return f_pitchDegrees;}
	inline qreal heading() const {return f_headingDegrees;}

protected:

private:
	qreal f_pitchDegrees, f_headingDegrees;
};

#endif // ENTITY_H
