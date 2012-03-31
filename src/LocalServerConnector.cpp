#include "LocalServerConnector.h"

#include <QDebug>

LocalServerConnector::LocalServerConnector()
{
	QThread* thread = new QThread(this);
	m_server = new LocalServer(thread);
	m_me = new Me(&world());
	qDebug() << "Initialized" << metaObject()->className();
	thread->start();

	// For this LocalServerConnector, we simply send the events of the client to the embedded server...
	connect(this, SIGNAL(postEvent(const ServerEvent*)), m_server, SLOT(takeEvent(const ServerEvent*)));
	// For this LocalServerConnector, we simply send the events of the embedded server to the client...
	connect(m_server, SIGNAL(postEvent(const ClientEvent*)), this, SLOT(takeEvent(const ClientEvent*)));
}


