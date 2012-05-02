#include "Inventory.h"
#include "blocks/Blocks.h"
#include "blocks/BlockDescriptor.h"

Inventory::Inventory(int maxWeight) : m_maxWeight(maxWeight), m_weight(0)
{
	for(int i = 0; i < NUMBER_OF_INVENTORY_SLOTS; ++i)
	{
		m_inventorySlots[i].id = 0;
		m_inventorySlots[i].quantity = 0;
	}
}

const InventorySlot& Inventory::inventorySlot(int slotNumber) const
{
	if(slotNumber >= 0 && slotNumber < NUMBER_OF_INVENTORY_SLOTS)
		return m_inventorySlots[slotNumber];
	else
		return m_inventorySlots[0];
}

int Inventory::weight() const
{
	return m_weight;
}

int Inventory::maxWeight() const
{
	return m_maxWeight;
}

bool Inventory::addOne(const int blockId)
{
	// Check if the player can carry one more block
	if(m_weight + Blocks::byId(blockId).weight() > m_maxWeight)
		return false;

	// Find the slot of this id
	for(int i = 0; i < NUMBER_OF_INVENTORY_SLOTS; ++i)
	{
		if(m_inventorySlots[i].id == blockId) {
			m_inventorySlots[i].quantity++;
			m_weight += Blocks::byId(blockId).weight();
			return true;
		}
	}

	// If we couldn't foud a slot take a void one :
	for(int i = 0; i < NUMBER_OF_INVENTORY_SLOTS; ++i)
	{
		if(m_inventorySlots[i].id == 0) {
			m_inventorySlots[i].id = blockId;
			m_inventorySlots[i].quantity++;
			m_weight += Blocks::byId(blockId).weight();
			return true;
		}
	}

	// otherwise there is a rare problem : player doesn't have enough slots
	return false;
}

bool Inventory::removeOne(const int blockId)
{
	// Find the slot of this id
	for(int i = 0; i < NUMBER_OF_INVENTORY_SLOTS; ++i)
	{
		if(m_inventorySlots[i].id == blockId && m_inventorySlots[i].quantity > 0) {
			m_inventorySlots[i].quantity--;
			m_weight -= Blocks::byId(blockId).weight();
			// If there is not any block, remove the id
			if(m_inventorySlots[i].quantity == 0) {
				m_inventorySlots[i].id = 0;
			}
			return true;
		}
	}
	return false; // fail: player doesn't have some block of this id
}

bool Inventory::add(const int blockId, const int amount)
{
	for(int i = 0; i < amount; ++i) {
		if(!addOne(blockId)) {
			return false;
		}
	}
	return true;
}
