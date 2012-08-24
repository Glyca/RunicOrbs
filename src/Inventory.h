#ifndef INVENTORY_H
#define INVENTORY_H

class Player;

const int NUMBER_OF_INVENTORY_SLOTS = 30;

/*! A slot of an inventory */
struct InventorySlot {
	int id;
	int quantity;
};

class Inventory
{
public:
	Inventory(Player* parentPlayer, int maxWeight);

	const InventorySlot& inventorySlot(int slotNumber) const;

	int weight() const;
	int maxWeight() const;

	/*! Try to add an item of the specified id to this slot */
	bool addOne(const int blockId);
	/*! Try to remove an item of the specified id to this inventory */
	bool removeOne(const int blockId);

	/*! Add several items of the same id to this inventory */
	bool add(const int blockId, const int amount);

private:
	Player* m_player; //!< The Player this Inventory belongs to
	InventorySlot m_inventorySlots[30]; //!< The slots of the inventory
	int m_maxWeight;
	int m_weight; //!< The total weight of all things this inventory contains
};

#endif // INVENTORY_H
