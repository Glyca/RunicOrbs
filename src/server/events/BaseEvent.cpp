#include "BaseEvent.h"

BaseEvent::BaseEvent(EventId eventId, QDataStream& stream)
	: QEvent(static_cast<QEvent::Type>(eventId))
{
	Q_UNUSED(stream);
}

BaseEvent::BaseEvent(EventId eventId) : QEvent(static_cast<QEvent::Type>(eventId))
{
}

BaseEvent::~BaseEvent()
{
}

void BaseEvent::serializeTo(QDataStream& stream) const
{
	Q_UNUSED(stream);
}
