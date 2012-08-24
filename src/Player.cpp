#include "server/events/BaseEvent.h"
#include "Player.h"

Player::Player(PhysicEngine* parentPhysicEngine, int id)
	: Entity(parentPhysicEngine, id), m_inventory(Inventory(1000)), i_selectedSlot(0)
{
	setMass(75.0);
}

Player::~Player()
{
}

bool Player::event(QEvent* event)
{
	BaseEvent* baseEvent = dynamic_cast<BaseEvent*>(event);
	if(baseEvent != 0) {

	}
}

Vector Player::eyePosition()
{
	Vector footPosition = v_position;
	footPosition.y += (PLAYER_HEIGHT - 0.10); // not 1.75 because eyes are a little bit under
	return footPosition;
}

int Player::currentLoad() const
{
	return m_inventory.weight();
}

int Player::maxLoad() const
{
	return m_inventory.maxWeight();
}

void Player::setSelectedSlot(const unsigned int slotNumber)
{
	if(slotNumber > VIEWABLE_INVENTORY_SIZE) {
		i_selectedSlot = 0;
	}
	else {
		i_selectedSlot = slotNumber;
	}
}

const InventorySlot& Player::inventorySlot(int slotNumber) const
{
	return m_inventory.inventorySlot(slotNumber); // Already performs checks on slotNumber
}

bool Player::giveOne(const int id)
{
	return m_inventory.addOne(id);
}

void Player::give(const int id, const int quantity)
{
	for(int i = 0; i < quantity; ++i) {
		if(!giveOne(id)) break;
	}
}

bool Player::takeOne(const int id)
{
	return m_inventory.removeOne(id);
}
