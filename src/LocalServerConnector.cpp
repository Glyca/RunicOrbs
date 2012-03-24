#include "LocalServerConnector.h"

#include <QDebug>

LocalServerConnector::LocalServerConnector()
{
	QThread* thread = new QThread(this);
	m_server = new LocalServer(thread);
	m_me = new Me(&world());
	qDebug() << "Initialized" << metaObject()->className();
	thread->start();

	// For this LocalServerConnector, we simply send the events to the embedded server...
	connect(this, SIGNAL(postEvent(const Event*)), m_server, SLOT(takeEvent(const Event*)));
}


