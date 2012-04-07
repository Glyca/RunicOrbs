#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "InventorySlot.h"

const unsigned int INVENTORY_SIZE = 8;

class Player : public Entity
{
public:
	Player(int id = 0);

	/*! The position of the eye of the player (useful for the camera) */
	Vector eyePosition();

	/*! The slot number that is selected */
	inline unsigned int selectedSlot() const {return i_selectedSlot;}
	/*! Modify selected inventory slot of the player */
	void setSelectedSlot(const unsigned int slotNumber);

	/*! Access to a slot of the inventory */
	InventorySlot& inventorySlot(const unsigned int slotNumber);
	/*! Try to give the block id to the player */
	bool giveOne(const int id);
	/*! Try to take one block of the specified id to the player */
	bool takeOne(const int id);

private:
	unsigned int i_selectedSlot; //!< Which slot of his inventory the player have selected
	InventorySlot m_inventorySlots[INVENTORY_SIZE]; //!< The inventory of the player
};

#endif // PLAYER_H
