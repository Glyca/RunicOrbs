#ifndef INVENTORYCHANGEDEVENT_H
#define INVENTORYCHANGEDEVENT_H

#include "PlayerEvent.h"

/*! This event is fired when the Inventory of a Player has changed */
class InventoryChangedEvent : public PlayerEvent
{
public:
	InventoryChangedEvent(EventId eventId, QDataStream& stream);
	InventoryChangedEvent(EventId eventId, quint32 playerId, quint32 slot, quint32 newQuantity);
	virtual ~InventoryChangedEvent();

	virtual void serializeTo(QDataStream& stream) const;

	quint32 slot() const;
	quint32 quantity() const;

private:
	quint32 i_slot;
	quint32 i_quantity; //!< The new quantity the slot has
};

#endif // INVENTORYCHANGEDEVENT_H
