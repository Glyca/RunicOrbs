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
		return true;
	}
}

bool InventorySlot::addOne()
{
	i_amount++; // For the moment we can add unlimited blocks to a slot
	return true;
}
