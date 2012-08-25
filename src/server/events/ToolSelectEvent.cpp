#include "ToolSelectEvent.h"

ToolSelectEvent::ToolSelectEvent(EventId eventId, QDataStream& stream)
	: BaseEvent(eventId, stream), PlayerEvent(eventId, stream)
{
}

ToolSelectEvent::ToolSelectEvent(EventId eventId, quint32 playerId, quint32 slot, quint32 tool)
	: BaseEvent(eventId), PlayerEvent(eventId, playerId), i_slot(slot), i_tool(tool)
{
}

ToolSelectEvent::~ToolSelectEvent()
{
}

void ToolSelectEvent::serializeTo(QDataStream& stream) const
{
	PlayerEvent::serializeTo(stream);

	stream << i_slot;
	stream << i_tool;
}

quint32 ToolSelectEvent::slot() const
{
	return i_slot;
}

quint32 ToolSelectEvent::tool() const
{
	return i_tool;
}

