#ifndef CLIENTEVENT_H
#define CLIENTEVENT_H

#include "Event.h"
#include "ServerConnector.h"

class ClientEvent : public Event
{
public:
	ClientEvent();

	/*! Do the event on the specified ServerConnector */
	virtual void perform(ServerConnector& connector) const = 0;
};

#endif // CLIENTEVENT_H
