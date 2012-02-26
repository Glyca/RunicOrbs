#include "LocalServerConnector.h"

#include <QDebug>

LocalServerConnector::LocalServerConnector()
{
	qDebug() << "Initialized" << metaObject()->className();
}

