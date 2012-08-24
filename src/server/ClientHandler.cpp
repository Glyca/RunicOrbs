#include <QThread>

#include "ClientHandler.h"
#include "Log.h"

ClientHandler::ClientHandler(int socketDescriptor, MultiplayerServer* server) : m_parentServer(server), b_socketCreated(false), i_socketDescriptor(socketDescriptor)
{
}

ClientHandler::~ClientHandler()
{
	if(b_socketCreated) {
		m_socket->disconnectFromHost();
		delete m_socket;
	}
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

void ClientHandler::readyRead()
{
	ldebug(Channel_Server, QString("Received data: %1").arg(QString(m_socket->readAll())));
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
