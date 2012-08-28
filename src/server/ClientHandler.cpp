#include <QThread>

#include "server/events/BaseEvent.h"
#include "ClientHandler.h"
#include "Log.h"
#include "MultiplayerServer.h"
#include "version.h"

ClientHandler::ClientHandler(int socketDescriptor, MultiplayerServer* server)
	: m_parentServer(server), b_socketCreated(false), i_socketDescriptor(socketDescriptor), m_player(NULL)
{
}

ClientHandler::~ClientHandler()
{
	if(b_socketCreated) {
		m_socket->disconnectFromHost();
		delete m_socket;
	}
}

QTcpSocket& ClientHandler::socket()
{
	return *m_socket;
}

void ClientHandler::bind()
{
	ldebug(Channel_Server, "Binding client...");

	m_socket = new QTcpSocket(this);
	b_socketCreated = true;

	connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
	connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
	connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

	if (!m_socket->setSocketDescriptor(i_socketDescriptor))
	{
		emit error(m_socket->error());
	}
}

void ClientHandler::connected()
{
	ldebug(Channel_Server, "Client connected!");
}

void ClientHandler::readyRead() // There is some data to read
{
	NetworkTalker::readyRead();
}

void ClientHandler::disconnected()
{
	ldebug(Channel_Server, "Client disconnected!");
}

void ClientHandler::sendPlayerEvent(BaseEvent* baseEvent)
{
	if(!baseEvent->transmitted()) {
		sendEvent(baseEvent);
	}
}

void ClientHandler::error(QAbstractSocket::SocketError socketError)
{
	switch (socketError) {
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		lwarning(Channel_Server, tr("The host was not found. Please check the host name and port settings."));
		break;
	case QAbstractSocket::ConnectionRefusedError:
		lwarning(Channel_Server, tr("The connection was refused by the peer. "
									"Make sure the server is running, "
									"and check that the host name and port "
									"settings are correct."));
		break;
	default:
		lwarning(Channel_Server, tr("The following error occurred: %1.").arg(m_socket->errorString()));
	}
}

void ClientHandler::readPacket(QByteArray& data)
{
	if(!b_versionConfirmed) {
		if(QByteArray(TRO_VERSION) == data)
		{
			ldebug(Channel_Server, tr("version: OK"));
			b_versionConfirmed = true;
		}
		else {
			sendPacket(QByteArray(BAD_VERSION));
			disconnect();
		}
	}

	else if(!b_identityConfirmed) {
		if(true) { // nickname validity check
			ldebug(Channel_Server, tr("nickname \"%1\" : OK").arg(QString::fromUtf8(data)));
			b_identityConfirmed = true;

			m_player = m_parentServer->newPlayer();

			sendPacket(QByteArray(PLAYER_ID_FOLLOWING));
			sendPacket(QString::number(m_player->id()).toUtf8());

			connect(m_player, SIGNAL(eventReceived(BaseEvent*)), this, SLOT(sendPlayerEvent(BaseEvent*)));
			m_parentServer->connectPlayer(m_player);
			m_parentServer->world()->connectPlayer(m_player);
		}
		else {
			sendPacket(QByteArray(BAD_NICKNAME));
			disconnect();
		}
	}

	else {
		NetworkTalker::readPacket(data);
	}
}

void ClientHandler::processReadEvent(BaseEvent* event)
{
	QCoreApplication::postEvent(reinterpret_cast<QObject*>(m_parentServer), reinterpret_cast<QEvent*>(event));
}

void ClientHandler::disconnect()
{
	m_socket->waitForBytesWritten();
	m_socket->disconnectFromHost();
}
