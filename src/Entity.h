#ifndef ENTITY_H
#define ENTITY_H

#include "PhysicObject.h"

class Entity : public PhysicObject
{
public:
	Entity(int id = 0);
	virtual ~Entity();

	virtual Vector velocity() const;

	/*! The direction the entity is looking at */
	Vector direction() const;
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
		if(f_yawDegrees < 0.0f) f_yawDegrees = 360.0f;
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
	inline void stopWalking(WalkDirection direction) {m_walkDirection = (WalkDirection)(m_walkDirection & ~direction);}
	/*! Stop the Entity walking */
	inline void stopWalking() {m_walkDirection = WalkDirection_Stop; v_walkVelocity.null();}
	/*! Wether the Entity is walking or not */
	inline bool isWalking() const {return !(m_walkDirection == WalkDirection_Stop);}

	inline void jump() {b_jumping = true;}
	inline void stopJumping() {b_jumping = false;}
	inline bool isJumping() const {return b_jumping;}

protected:
	void processMove(const preal f_elapsedTimeSec);

private:
	float f_pitchDegrees, f_yawDegrees;

	WalkDirection m_walkDirection;
	Vector v_walkVelocity;

	bool b_jumping;
};

#endif // ENTITY_H
