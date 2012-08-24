#ifndef PLAYEREVENT_H
#define PLAYEREVENT_H

#include "BaseEvent.h"

class PlayerEvent : virtual public BaseEvent
{
public:
	PlayerEvent(EventId eventId, QDataStream& stream);
	PlayerEvent(EventId eventId, quint32 playerId);
	virtual ~PlayerEvent();

	virtual void serializeTo(QDataStream& stream) const;

	quint32 playerId() const;

private:
	quint32 i_playerId;
};

#endif // PLAYEREVENT_H
