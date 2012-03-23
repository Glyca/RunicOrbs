#include "server/events/BlockPickEvent.h"
#include "server/events/BlockUseEvent.h"
#include "ServerConnector.h"

#include <QDebug>

ServerConnector::ServerConnector(QObject *parent) : QObject(parent)
{
	qDebug() << "Initialized" << metaObject()->className();
}

World& ServerConnector::world()
{
	Q_ASSERT(1!=1);
	return *(World*)0x123456789; // TODO WARNING : we can't access a world from a ServerConnector, only with its children.
}

void ServerConnector::pickBlock()
{
	BlockPickEvent* event = new BlockPickEvent(me()->pointedBlock(), me());
	emit postEvent(event);
}

void ServerConnector::useBlock()
{
	BlockUseEvent* event = new BlockUseEvent(me()->pointedFreeBlock(), me());
	emit postEvent(event);
}
