#ifndef SLOTSELECTEVENT_H
#define SLOTSELECTEVENT_H

#include "PlayerEvent.h"

const int EVENTID_SLOTSELECT = 3;

/*! Event fired when the player changes the the block or tool he holds  */
class SlotSelectEvent : public PlayerEvent
{
public:
	SlotSelectEvent(const int selectedSlot, Player* player);

	inline virtual int id() {return EVENTID_SLOTSELECT;}

	virtual void perform(Server& server) const;
	virtual QByteArray serialize() const;

protected:
	int i_selectedSlot;
};

#endif // SLOTSELECTEVENT_H
