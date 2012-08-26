#include <QThread>

#include "ClientHandler.h"
#include "Log.h"
#include "version.h"

ClientHandler::ClientHandler(int socketDescriptor, MultiplayerServer* server)
	: m_parentServer(server), b_socketCreated(false), i_socketDescriptor(socketDescriptor)
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
	Q_UNUSED(event);
}

void ClientHandler::disconnect()
{
	m_socket->waitForBytesWritten();
	m_socket->disconnectFromHost();
}
