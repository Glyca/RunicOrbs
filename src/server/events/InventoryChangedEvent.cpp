#include "InventoryChangedEvent.h"

InventoryChangedEvent::InventoryChangedEvent(EventId eventId, QDataStream& stream)
	: BaseEvent(eventId, stream), PlayerEvent(eventId, stream)
{
	stream >> i_slot;
	stream >> i_quantity;
}

InventoryChangedEvent::InventoryChangedEvent(EventId eventId, quint32 playerId, quint32 slot, quint32 newQuantity)
	: BaseEvent(eventId), PlayerEvent(eventId, playerId), i_slot(slot), i_quantity(newQuantity)
{
}

InventoryChangedEvent::~InventoryChangedEvent()
{
}

void InventoryChangedEvent::serializeTo(QDataStream& stream) const
{
	PlayerEvent::serializeTo(stream);

	stream << i_slot;
	stream << i_quantity;
}

quint32 InventoryChangedEvent::slot() const
{
	return i_slot;
}

quint32 InventoryChangedEvent::quantity() const
{
	return i_quantity;
}
