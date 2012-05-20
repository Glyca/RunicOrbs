#ifndef BIEVENT_H
#define BIEVENT_H

#include "ClientEvent.h"
#include "ServerEvent.h"

/*! An ClientEvent and ServerEvent Event that can be sended to a client and a server */
class BiEvent : public ClientEvent, public ServerEvent
{
public:
	BiEvent();
};

#endif // BIEVENT_H
