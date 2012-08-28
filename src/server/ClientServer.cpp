#include <QtGui/QMessageBox>

#include "server/events/ChunkNewDataEvent.h"
#include "ClientServer.h"
#include "Log.h"
#include "version.h"

ClientServer::ClientServer(const QString &hostName, quint16 port, const QString& nickName)
	: Server(qApp, 123456789), s_hostname(hostName), i_port(port), s_nickName(nickName), b_connected(false), b_playerIdFollowing(false)
{
	QObject::connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
			this, SLOT(displayError(QAbstractSocket::SocketError)));
	QObject::connect(&m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
	QObject::connect(&m_socket, SIGNAL(connected()), this, SIGNAL(connected()));
	QObject::connect(this, SIGNAL(connected()), this, SLOT(onConnected()));
	QObject::connect(&m_socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
	QObject::connect(this, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

ClientServer::~ClientServer()
{
	m_socket.abort();
}

void ClientServer::sendNewChunkDataToPlayer(Chunk* chunk, quint32 playerId)
{
	Q_UNUSED(chunk); Q_UNUSED(playerId);
}

bool ClientServer::event(QEvent* event)
{
	// If this is a The Runic Orbs event
	BaseEvent* theBaseEvent = dynamic_cast<BaseEvent*>(event);
	if(theBaseEvent != 0)
	{
		if(!theBaseEvent->transmitted())
		{
			sendEvent(theBaseEvent);
			return true;
		}
		else
		{
			return EventReadyObject::event(event);
		}
	}
}

/*bool ClientServer::baseEvent(BaseEvent* baseEvent)
{
	if(!baseEvent->transmitted()) {
		sendEvent(baseEvent);
		return true;
	}
	else {
		return false;
	}
}

bool ClientServer::worldEvent(WorldEvent* worldEvent)
{
	return false;
}*/

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

	else if(data == QByteArray(PLAYER_ID_FOLLOWING)) {
		b_playerIdFollowing = true;
	}

	else if(b_playerIdFollowing) {
		b_playerIdFollowing = false;

		int id = QString::fromUtf8(data.data()).toInt();

		Player* myPlayer = new Player(m_world->physicEngine(), id);
		this->connectPlayer(myPlayer);
		m_world->connectPlayer(myPlayer);

		emit playerReady(id);
	}

	else {
		NetworkTalker::readPacket(data);
	}
}

void ClientServer::processReadEvent(BaseEvent* event)
{
	QCoreApplication::postEvent(this, event);
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

void ClientServer::readyRead()
{
	NetworkTalker::readyRead();
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
