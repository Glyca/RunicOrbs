#ifndef SERVEREVENT_H
#define SERVEREVENT_H

#include "Event.h"

class Server; // To avoid circular inclusions

/*! An Event fired by a client to a Server */
class ServerEvent : public Event
{
public:
	ServerEvent();

	/*! Do the event on the specified Server */
	virtual void perform(Server& server) const = 0;
};

#endif // SERVEREVENT_H
