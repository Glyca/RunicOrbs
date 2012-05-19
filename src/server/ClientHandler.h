#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>

class MultiplayerServer;

class ClientHandler : public QObject
{
	Q_OBJECT
public:
	explicit ClientHandler(int socketDescriptor, MultiplayerServer* server);

signals:
	void error(QAbstractSocket::SocketError socketError);

public slots:
	/*! Create m_socket and set its i_socketDescriptor, connecting the client.
		This slot is not called in the main thread, thus the socket lives in another thread. */
	void bind();

	void connected();
	void readyRead();
	void disconnected();

private:
	MultiplayerServer* m_parentServer; //!< The MultiplayerServer where the ClientHandler lives
	bool b_binded; //!< If the m_socket is created and binded
	int i_socketDescriptor; //!< handle used to bind the m_socket
	QTcpSocket* m_socket; //!< The TCP socket
};

#endif // CLIENTHANDLER_H
