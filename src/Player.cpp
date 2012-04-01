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
	// Let's find a slot of this id to put the block
	for(int s = 0; s < INVENTORY_SIZE; ++s)
	{
		// If we added the block to the slot successfully
		if(inventorySlot(s).addOne(id)) {
			return true;
		}
	}
	// We didn't find any free slot
	return false;
}

bool Player::takeOne(const int id)
{
	// If the slot is already of the type id
	return inventorySlot(selectedSlot()).removeOne(id);
}
