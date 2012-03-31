#ifndef WALKEVENT_H
#define WALKEVENT_H

#include "Event.h"
#include "Entity.h"

const int EVENTID_WALK = 3;

class MoveEvent : public Event
{
public:
	MoveEvent(const Entity::WalkDirection direction, Entity* entity);

	inline virtual int id() {return EVENTID_WALK;}

	virtual void perform(Server& server) const;
	virtual QByteArray serialize() const;

protected:
	Entity::WalkDirection m_direction;
	Entity* m_entity;
};

#endif // WALKEVENT_H
