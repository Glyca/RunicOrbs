#ifndef BASEEVENT_H
#define BASEEVENT_H

#include <QDataStream>
#include <QEvent>
#include "EventIds.h"

/*! The root event for all events

  Event parent is a Server or a ServerConnector.
  Events don't perform any check on the size of the stream given to them.
  In all cases, the stream used for unserialization (in contructor) must have all data ready to be read

  The b_transmitted attribute avoids sending again an event on the network while the network itself has sent it to us.

*/
class BaseEvent : public QEvent
{
public:
	/*! Create an event of id eventId and unserialize the data from stream */
	BaseEvent(EventId eventId, QDataStream& stream);
	BaseEvent(EventId eventId);
	virtual ~BaseEvent();

	EventId type() const;

	virtual void serializeTo(QDataStream& stream) const;

	bool transmitted() const;
	void setTransmitted(bool yes);

private:
	bool b_transmitted; //!< If this event has already transited on the network, so it can do it if not
};

#endif // BASEEVENT_H
