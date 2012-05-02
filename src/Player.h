#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Inventory.h"

const unsigned int VIEWABLE_INVENTORY_SIZE = 8;

class Player : public Entity
{
public:
	Player(int id = 0);

	/*! The position of the eye of the player (useful for the camera) */
	Vector eyePosition();

	/*! Return the weight of items carried by the player */
	int currentLoad() const;
	int maxLoad() const;

	/*! The slot number that is selected */
	inline unsigned int selectedSlot() const {return i_selectedSlot;}
	/*! Modify selected inventory slot of the player */
	void setSelectedSlot(const unsigned int slotNumber);

	/*! Access to a slot of the inventory */
	const InventorySlot& inventorySlot(int slotNumber) const;
	/*! Try to give the block id to the player */
	bool giveOne(const int id);
	/*! Try to give quantity block id to the player */
	void give(const int id, const int quantity);
	/*! Try to take one block of the specified id to the player */
	bool takeOne(const int id);

private:
	Inventory m_inventory; //!< The inventory of the player
	unsigned int i_selectedSlot; //!< Which slot of his inventory the player have selected
};

#endif // PLAYER_H
