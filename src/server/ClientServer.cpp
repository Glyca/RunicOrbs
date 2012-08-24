#include <QtGui/QMessageBox>

#include "ClientServer.h"

ClientServer::ClientServer(const QString &hostName, quint16 port)
	: Server(this, 123456789), s_hostname(hostName), i_port(port), b_connected(false)
{
	QObject::connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
			this, SLOT(displayError(QAbstractSocket::SocketError)));
	QObject::connect(&m_socket, SIGNAL(connected()), this, SIGNAL(connected()));
	QObject::connect(this, SIGNAL(connected()), this, SLOT(onConnected()));
}

ClientServer::~ClientServer()
{
}

bool ClientServer::connect()
{
	m_socket.abort();
	m_socket.connectToHost(s_hostname, i_port);
	m_socket.waitForConnected();
	return b_connected;
}

void ClientServer::onConnected()
{
	b_connected = true;
}

void ClientServer::displayError(QAbstractSocket::SocketError socketError)
 {
	 switch (socketError) {
	 case QAbstractSocket::RemoteHostClosedError:
		 break;
	 case QAbstractSocket::HostNotFoundError:
		 QMessageBox::information(0, QString("The Runic Orbs"),
								  tr("The host was not found. Please check the host name and port settings."));
		 break;
	 case QAbstractSocket::ConnectionRefusedError:
		 QMessageBox::information(0, QString("The Runic Orbs"),
								  tr("The connection was refused by the peer. "
									 "Make sure the server is running, "
									 "and check that the host name and port "
									 "settings are correct."));
		 break;
	 default:
		 QMessageBox::information(0, QString("The Runic Orbs"),
								  tr("The following error occurred: %1.").arg(m_socket.errorString()));
	 }
 }
