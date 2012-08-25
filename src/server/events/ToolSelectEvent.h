#ifndef TOOLSELECTEVENT_H
#define TOOLSELECTEVENT_H

#include "PlayerEvent.h"

/*! This event is sended when a Player choses a new tool/slot of this inventory */
class ToolSelectEvent : public PlayerEvent
{
public:
	ToolSelectEvent(EventId eventId, QDataStream& stream);
	ToolSelectEvent(EventId eventId, quint32 playerId, quint32 slot, quint32 tool);
	virtual ~ToolSelectEvent();

	virtual void serializeTo(QDataStream& stream) const;

	quint32 slot() const;
	quint32 tool() const;

private:
	quint32 i_slot;
	quint32 i_tool;
};

#endif // TOOLSELECTEVENT_H
