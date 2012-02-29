#ifndef ENTITY_H
#define ENTITY_H

#include "PhysicObject.h"

class Entity : public PhysicObject
{
public:
	Entity();

	/*! The direction the entity is looking at */
	Vector direction();
	inline float pitch() const {return f_pitchDegrees;}
	inline void pitch(const float pitchDegrees)
	{
		f_pitchDegrees = pitchDegrees;
                if(f_pitchDegrees < 91.0f) f_pitchDegrees = 91.0f;
                if(f_pitchDegrees > 269.0f) f_pitchDegrees = 269.0f;
	}
	inline float heading() const {return f_headingDegrees;}
	inline void heading(const float headingDegrees)
	{
		f_headingDegrees = headingDegrees;
		if(f_headingDegrees < -360.0f) f_headingDegrees = 0.0f;
		if(f_headingDegrees > 360.0f) f_headingDegrees = 0.0f;
	}

	typedef enum {WalkingDirection_Stop = 0,
				  WalkingDirection_Forward = 1,
				  WalkingDirection_Backward = 2,
				  WalkingDirection_Left = 4,
				  WalkingDirection_Right = 8} WalkingDirection;

	/*! Make the Entity walk to the direction direction */
	inline void walk(WalkingDirection direction) {m_walkingDirection = (WalkingDirection)(m_walkingDirection | direction);}
	/*! Stop the Entity walking for a direction */
	inline void stopWalk(WalkingDirection direction) {m_walkingDirection = (WalkingDirection)(m_walkingDirection & ~direction);}
	/*! Stop the Entity walking */
	inline void stopWalk() {m_walkingDirection = WalkingDirection_Stop;}
	/*! Wether the Entity is walking or not */
	inline bool walking() const {return !(m_walkingDirection == WalkingDirection_Stop);}


protected:
	void processMove(preal f_elapsedTimeSec, World& workingWorld);

private:
	float f_pitchDegrees, f_headingDegrees;
	bool b_walking;
	WalkingDirection m_walkingDirection;
	Vector v_oldWalkingVelocity;
};

#endif // ENTITY_H
