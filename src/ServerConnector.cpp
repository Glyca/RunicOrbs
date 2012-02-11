#include "ServerConnector.h"

ServerConnector::ServerConnector(QObject *parent) :
	QObject(parent)
{
	m_me = new Me();
}

Me& ServerConnector::me() const
{
	return *m_me;
}
