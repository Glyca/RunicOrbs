#include "InventorySlot.h"

InventorySlot::InventorySlot() : i_id(0), i_amount(0)
{
}

bool InventorySlot::removeOne()
{
	if(i_amount <= 0) {
		return false;
	}
	else {
		i_amount--;
		// Remove the id if we don't have any block in this slot
		if(i_amount == 0) {
			i_id = 0;
		}
		return true;
	}
}

bool InventorySlot::removeOne(const int id)
{
	if(i_id == id) {
		return removeOne();
	}
	// If this slot is not of type id, we can't remove a block of it
	return false;
}

bool InventorySlot::addOne()
{
	i_amount++; // For the moment we can add unlimited blocks to a slot
	return true;
}

bool InventorySlot::addOne(const int id)
{
	if(i_id == id) {
		return addOne();
	}
	// If there is no id for this slot
	else if(i_id == 0) {
		i_id = id;
		return addOne();
	}
	// Else we can't add this id to this slot
	return false;
}
