#include "ServerConnector.h"

#include <QDebug>

ServerConnector::ServerConnector(QObject *parent) : QObject(parent)
{
	qDebug() << "Initialized" << metaObject()->className();
}

World& ServerConnector::world()
{

}
