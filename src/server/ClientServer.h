#ifndef CLIENTSERVER_H
#define CLIENTSERVER_H

#include <QtNetwork/QTcpSocket>

#include "NetworkTalker.h"
#include "Server.h"

/*! Server run by a client in a multiplayer game.
 This server is like a copy of the remote server it is connected to,
 but it can't generate chunks or other things by itself.
 Instead, it sends events to the remote Server to load these Chunks.
*/
class ClientServer : public Server, public NetworkTalker
{
	Q_OBJECT
public:
	ClientServer(const QString& hostName, quint16 port, const QString& nickName);
	virtual ~ClientServer();

	virtual bool connect();
	virtual World& world() { return *m_world; }

signals:
	void connected();
	void disconnected();

private:
	virtual bool baseEvent(BaseEvent* baseEvent);

	virtual QTcpSocket& socket();
	virtual void readPacket(QByteArray& data);

	virtual void processReadEvent(BaseEvent* event);

private slots:
	void onConnected();
	void onDisconnected();
	void displayError(QAbstractSocket::SocketError socketError);

private:
	QTcpSocket m_socket;
	QString s_hostname;
	quint16 i_port;
	QString s_nickName;
	bool b_connected;
};

#endif // CLIENTSERVER_H
