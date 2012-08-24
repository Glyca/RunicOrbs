#ifndef BASEEVENT_H
#define BASEEVENT_H

#include <QDataStream>
#include <QEvent>
#include "EventIds.h"

/*! The root event for all events

  Event parent is a Server or a ServerConnector.
  Events don't perform any check on the size of the stream given to them.
  In all cases, the stream used for unserialization (in contructor) must have all data ready to be read

*/
class BaseEvent : public QEvent
{
public:
	/*! Create an event of id eventId and unserialize the data from stream */
	BaseEvent(EventId eventId, QDataStream& stream);
	BaseEvent(EventId eventId);
	virtual ~BaseEvent();

	virtual void serializeTo(QDataStream& stream) const;
};

#endif // BASEEVENT_H
