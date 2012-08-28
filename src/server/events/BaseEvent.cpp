#include "BaseEvent.h"

BaseEvent::BaseEvent(EventId eventId, QDataStream& stream)
	: QEvent(static_cast<QEvent::Type>(eventId)), b_transmitted(false)
{
	Q_UNUSED(stream);
}

BaseEvent::BaseEvent(EventId eventId) : QEvent(static_cast<QEvent::Type>(eventId)), b_transmitted(false)
{
}

BaseEvent::~BaseEvent()
{
}

EventId BaseEvent::type() const
{
	return static_cast<EventId>(QEvent::type());
}

void BaseEvent::serializeTo(QDataStream& stream) const
{
	Q_UNUSED(stream);
}

bool BaseEvent::transmitted() const
{
	return b_transmitted;
}

void BaseEvent::setTransmitted(bool yes)
{
	b_transmitted = yes;
}
