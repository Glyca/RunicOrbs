#include "server/events/PlayerEvent.h"
#include "Player.h"

Player::Player(PhysicEngine* parentPhysicEngine, int id)
	: Entity(parentPhysicEngine, id), m_inventory(new Inventory(this, 1000)), i_selectedSlot(0)
{
	setMass(100.0); // deliberately high
}

Player::~Player()
{
	delete m_inventory;
}

bool Player::event(QEvent* event)
{
	PlayerEvent* playerEvent = dynamic_cast<PlayerEvent*>(event);
	if(playerEvent != 0) {
		if(playerEvent->playerId() == this->id()) // This event is for this Player
		{
			emit eventReceived(playerEvent);
		}
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
	return m_inventory->weight();
}

int Player::maxLoad() const
{
	return m_inventory->maxWeight();
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
	return m_inventory->inventorySlot(slotNumber); // Already performs checks on slotNumber
}

bool Player::giveOne(const int id)
{
	return m_inventory->addOne(id);
}

void Player::give(const int id, const int quantity)
{
	for(int i = 0; i < quantity; ++i) {
		if(!giveOne(id)) break;
	}
}

bool Player::takeOne(const int id)
{
	return m_inventory->removeOne(id);
}
