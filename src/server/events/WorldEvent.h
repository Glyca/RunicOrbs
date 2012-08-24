#ifndef WORLDEVENT_H
#define WORLDEVENT_H

#include "BaseEvent.h"

/*! A BaseEvent that happened in a World
  Compared to the BaseEvent, it contains one more information about the World where the event occurred
*/
class WorldEvent : virtual public BaseEvent
{
public:
	WorldEvent(EventId eventId, QDataStream& stream);
	WorldEvent(EventId eventId, quint32 worldId);
	virtual ~WorldEvent();

	virtual void serializeTo(QDataStream& stream) const;

private:
	quint32 i_worldId;
};

#endif // WORLDEVENT_H
