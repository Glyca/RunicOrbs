#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Inventory.h"

class BaseEvent;

const unsigned int VIEWABLE_INVENTORY_SIZE = 8;

class Player : public Entity
{
	Q_OBJECT
public:
	Player(PhysicEngine* parentPhysicEngine, int id = 0);
	virtual ~Player();

	virtual bool event(QEvent* event);

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

signals:
	/*! This signal is emitted when the Player receive a BaseEvent.
	Usually, for a local game, this signal is connected to a slot of a LocalServerConnector ;
	and for a multiplayer game, this is connected to a slot of the associated ClientHandler */
	/*void eventReceived(BaseEvent* baseEvent);*/

private:
	Inventory m_inventory; //!< The inventory of the player
	unsigned int i_selectedSlot; //!< Which slot of his inventory the player have selected
};

#endif // PLAYER_H
