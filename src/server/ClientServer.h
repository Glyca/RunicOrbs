#ifndef CLIENTSERVER_H
#define CLIENTSERVER_H

#include <QtNetwork/QTcpSocket>

#include "Server.h"

/*! Server run by a client in a multiplayer game.
 This server is like a copy of the remote server it is connected to,
 but it can't generate chunks or other things by itself.
 Instead, it sends events to the remote Server to load these Chunks.
*/
class ClientServer : public Server
{
public:
	ClientServer(const QString& hostName, quint16 port);
	virtual ~ClientServer();

	virtual bool connect();

	virtual World& world() { return *m_world; }

signals:
	void connected();

private slots:
	void onConnected();
	void displayError(QAbstractSocket::SocketError socketError);

private:
	QTcpSocket m_socket;
	QString s_hostname;
	quint16 i_port;
	bool b_connected;
};

#endif // CLIENTSERVER_H
