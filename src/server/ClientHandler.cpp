#include <QThread>

#include "ClientHandler.h"
#include "Log.h"

ClientHandler::ClientHandler(int socketDescriptor, MultiplayerServer* server) : m_parentServer(server), b_binded(false), i_socketDescriptor(socketDescriptor)
{
}

void ClientHandler::bind()
{
	ldebug(Channel_Server, "Binding client...");

	m_socket = new QTcpSocket(this);

	connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
	connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(error(QAbstractSocket::SocketError)));
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
