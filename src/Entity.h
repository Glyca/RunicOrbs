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
	inline float yaw() const {return f_yawDegrees;}
	inline void yaw(const float yawDegrees)
	{
		f_yawDegrees = yawDegrees;
		if(f_yawDegrees < -360.0f) f_yawDegrees = 0.0f;
		if(f_yawDegrees > 360.0f) f_yawDegrees = 0.0f;
	}

	typedef enum {WalkDirection_Stop = 0,
				  WalkDirection_Forward = 1,
				  WalkDirection_Backward = 2,
				  WalkDirection_Left = 4,
				  WalkDirection_Right = 8} WalkDirection;

	/*! Make the Entity walk to the direction direction */
	inline void walk(WalkDirection direction) {m_walkDirection = (WalkDirection)(m_walkDirection | direction);}
	/*! Stop the Entity walking for a direction */
	inline void stopWalk(WalkDirection direction) {m_walkDirection = (WalkDirection)(m_walkDirection & ~direction);}
	/*! Stop the Entity walking */
	inline void stopWalk() {m_walkDirection = WalkDirection_Stop;}
	/*! Wether the Entity is walking or not */
	inline bool walking() const {return !(m_walkDirection == WalkDirection_Stop);}


protected:
	void processMove(preal f_elapsedTimeSec, World& workingWorld);

private:
	float f_pitchDegrees, f_yawDegrees;
	bool b_walking;
	WalkDirection m_walkDirection;
	Vector v_oldWalkVelocity;
};

#endif // ENTITY_H
