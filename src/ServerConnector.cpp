#include "ServerConnector.h"

ServerConnector::ServerConnector(QObject *parent) :
	QObject(parent)
{
	m_me = new Me();
	qDebug() << "Initialized " << metaObject()->className();
}

Me& ServerConnector::me() const
{
	return *m_me;
}
