#include "SlotSelectEvent.h"
#include "server/Server.h"

SlotSelectEvent::SlotSelectEvent(const int selectedSlot, Player* player) : PlayerEvent(player), i_selectedSlot(selectedSlot)
{
}

void SlotSelectEvent::perform(Server& server) const
{
	Q_UNUSED(server);
	m_player->setSelectedSlot(i_selectedSlot);
}

QByteArray SlotSelectEvent::serialize() const
{
	// TODO
	QByteArray byteArray;

	return byteArray;
}

