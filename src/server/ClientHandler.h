#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>

#include "NetworkTalker.h"

class MultiplayerServer;
class Player;

/*! Handle the TCP connection between a client and a MultiplayerServer */
class ClientHandler : public QObject, public NetworkTalker
{
	Q_OBJECT
public:
	explicit ClientHandler(int socketDescriptor, MultiplayerServer* server);
	virtual ~ClientHandler();

	void disconnect();

public slots:
	/*! Create m_socket and set its i_socketDescriptor, connecting the client.
		This slot is not called from the main thread, thus the socket lives in another thread. */
	void bind();

	void connected();
	void readyRead();
	void disconnected();

	/*! Send a BaseEvent received by the Player
		\sa Player::eventReceived */
	void sendPlayerEvent(BaseEvent* baseEvent);

	void error(QAbstractSocket::SocketError socketError);

private:
	virtual QTcpSocket& socket();
	virtual void readPacket(QByteArray& data);

	virtual void processReadEvent(BaseEvent* event);

	MultiplayerServer* m_parentServer; //!< The MultiplayerServer where the ClientHandler lives
	bool b_socketCreated; //!< If the m_socket is created and binded
	int i_socketDescriptor; //!< handle used to bind the m_socket
	QTcpSocket* m_socket; //!< The TCP socket

	bool b_versionConfirmed; //!< If the client version is ok (no = kick)
	bool b_identityConfirmed; //!< If the client has sent his nickname (bad one = kick)

	Player* m_player; //!< The Player which this ClientHandler is the relay
};

#endif // CLIENTHANDLER_H
