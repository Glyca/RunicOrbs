#include "PlayerEvent.h"

PlayerEvent::PlayerEvent(EventId eventId, QDataStream& stream) : BaseEvent(eventId, stream)
{
	stream >> i_playerId;
}

PlayerEvent::PlayerEvent(EventId eventId, quint32 playerId) : BaseEvent(eventId), i_playerId(playerId)
{
}

PlayerEvent::~PlayerEvent()
{
}

void PlayerEvent::serializeTo(QDataStream& stream) const
{
	BaseEvent::serializeTo(stream);

	stream << i_playerId;
}

quint32 PlayerEvent::playerId() const
{
	return i_playerId;
}
