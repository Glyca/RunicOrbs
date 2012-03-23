#ifndef EVENT_H
#define EVENT_H

#include <QByteArray>
class Server;

/*! An abstract class for events */
class Event
{
public:
	Event();

	/*! Do the event on the specified server */
	virtual void perform(Server& server) const = 0;

	/*! Serialize the event, for example to be sent trought the network. */
	virtual QByteArray serialize() const = 0;
};

#endif // EVENT_H
