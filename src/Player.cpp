#include "Player.h"

Player::Player(int id) : Entity(id), i_selectedSlot(0)
{
}

Vector Player::eyePosition()
{
	Vector footPosition = v_position;
	footPosition.y += (PLAYER_HEIGHT - 0.10); // not 1.75 because eyes are a little bit under
	return footPosition;
}

void Player::setSelectedSlot(const unsigned int slotNumber)
{
	if(slotNumber > INVENTORY_SIZE) {
		i_selectedSlot = 0;
	}
	else {
		i_selectedSlot = slotNumber;
	}
}

InventorySlot& Player::inventorySlot(const unsigned int slotNumber)
{
	if(slotNumber > INVENTORY_SIZE) {
		return m_inventorySlots[0];
	}
	else {
		return m_inventorySlots[slotNumber];
	}
}

bool Player::giveOne(const int id)
{
	// If the slot is already of the type id
	if(inventorySlot(selectedSlot()).id() == id) {
		return inventorySlot(selectedSlot()).addOne();
	}
	// The slot is not of this block id
	else {
		// Let's fine a free slot
		for(int s = 0; s < INVENTORY_SIZE; ++s)
		{
			if(inventorySlot(s).id() == id) {
				return inventorySlot(s).addOne();
			}
			// The slot is not of this block id
			else {
				if(inventorySlot(s).id() == 0) {
					// Modify the type of the slot
					inventorySlot(s).setId(id);
					// and try to add one
					bool succeeded = inventorySlot(s).addOne();
					if(!succeeded) { // If we couldn't add one more to this slot, remove the useless id
						inventorySlot(s).setId(0);
					}
					return succeeded;
				}
			}
		}
		// We didn't found any free slot
		return false;
	}
}

bool Player::takeOne(const int id)
{
	// If the slot is already of the type id
	if(inventorySlot(selectedSlot()).id() == id) {
		return inventorySlot(selectedSlot()).removeOne();
	}
	// The slot is not of this block id
	else {
		// Let's fine a slot with this id
		for(int s = 0; s < INVENTORY_SIZE; ++s)
		{
			if(inventorySlot(s).id() == id) {
				return inventorySlot(s).removeOne();
			}
		}
		// We didn't found any slot conaining this ressource
		return false;
	}
}
