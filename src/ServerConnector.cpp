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

