#include "InventorySetEvent.h"

InventorySetEvent::InventorySetEvent(int inventorySlot, int id, int amount) : i_inventorySlot(inventorySlot), i_id(id), i_amount(amount)
{
}


void InventorySetEvent::perform(ServerConnector& connector) const
{
	// For the moment, since we are only local, we just have to inform the game window that the inventory changed
	connector.makeInventoryRefreshed();
}

QByteArray InventorySetEvent::serialize() const
{
	// TODO
	QByteArray byteArray;

	return byteArray;
}

