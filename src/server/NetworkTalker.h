#ifndef NETWORKTALKER_H
#define NETWORKTALKER_H

#include <QTcpSocket>

class BaseEvent;

#define BAD_VERSION "BAD_VERSION"
#define BAD_NICKNAME "BAD_NICKNAME"

/*! Children of this convenient class are able to talk over the network in the same way */
class NetworkTalker
{
public:
	NetworkTalker();

protected:
	/*! Get the working socket */
	virtual QTcpSocket& socket() = 0;

	void readyRead();

	virtual void readPacket(QByteArray& data);
	virtual void sendPacket(const QByteArray& data);

	void readEvent(QByteArray& data);
	void sendEvent(BaseEvent* event);

	virtual void processReadEvent(BaseEvent* event) = 0;

private:
	quint32 i_packetSize; //!< The size of the packet we are waiting for
};

#endif // NETWORKTALKER_H
