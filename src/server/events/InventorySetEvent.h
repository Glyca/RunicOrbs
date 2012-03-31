#ifndef INVENTORYSETEVENT_H
#define INVENTORYSETEVENT_H

#include "ClientEvent.h"

const int EVENTID_INVENTORYSET = 4;

/*! This ClientEvent is fired to inform the client about changes to his inventory */
class InventorySetEvent : public ClientEvent
{
public:
	InventorySetEvent(int inventorySlot, int id, int amount);

	inline virtual int id() {return EVENTID_INVENTORYSET;}

	virtual void perform(ServerConnector& connector) const;
	virtual QByteArray serialize() const;

protected:
	int i_inventorySlot; //! Which slot do we set
	int i_id; //! Which id
	int i_amount; //! How many
};

#endif // INVENTORYSETEVENT_H
