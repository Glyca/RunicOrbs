#include <QtGui/QMessageBox>

#include "ClientServer.h"
#include "version.h"

ClientServer::ClientServer(const QString &hostName, quint16 port, const QString& nickName)
	: Server(qApp, 123456789), s_hostname(hostName), i_port(port), s_nickName(nickName), b_connected(false)
{
	QObject::connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
			this, SLOT(displayError(QAbstractSocket::SocketError)));
	QObject::connect(&m_socket, SIGNAL(connected()), this, SIGNAL(connected()));
	QObject::connect(this, SIGNAL(connected()), this, SLOT(onConnected()));
	QObject::connect(&m_socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
	QObject::connect(this, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

ClientServer::~ClientServer()
{
	m_socket.abort();
}

bool ClientServer::baseEvent(BaseEvent* baseEvent)
{
	sendEvent(baseEvent);
	delete baseEvent;
	return true;
}

QTcpSocket& ClientServer::socket()
{
	return m_socket;
}

void ClientServer::readPacket(QByteArray& data)
{
	if(data == QByteArray(BAD_VERSION)) {
		QMessageBox::information(0, QString("The Runic Orbs"),
								 tr("Your version of the game doesn't math server's one.\n"
									"Please update the game."));
	}

	else if(data == QByteArray(BAD_NICKNAME)) {
		QMessageBox::information(0, QString("The Runic Orbs"),
								 tr("Your nickname is already used or is forbidden.\n"
									"Please use another one."));
	}

	else {
		NetworkTalker::readPacket(data);
	}
}

void ClientServer::processReadEvent(BaseEvent* event)
{
	Q_UNUSED(event);
}

bool ClientServer::connect()
{
	m_socket.abort();
	m_socket.connectToHost(s_hostname, i_port);
	m_socket.waitForConnected();

	sendPacket(QByteArray(TRO_VERSION));
	sendPacket(s_nickName.toUtf8());

	return b_connected;
}

void ClientServer::onConnected()
{
	b_connected = true;
}

void ClientServer::onDisconnected()
{
	QMessageBox::information(0, QString("The Runic Orbs"),
							 tr("The server has closed the connection unexpectedly."));
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
