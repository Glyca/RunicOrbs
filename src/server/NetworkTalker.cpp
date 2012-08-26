#include "server/events/BlockChangedEvent.h"
#include "server/events/InventoryChangedEvent.h"
#include "server/events/PlayerBlockEvent.h"
#include "server/events/ToolSelectEvent.h"
#include "NetworkTalker.h"

NetworkTalker::NetworkTalker() : i_packetSize(0)
{
}

void NetworkTalker::readyRead() // There is some data to read
{
	if(i_packetSize == 0) // we don't know about the size of the packet
	{
		if(socket().bytesAvailable() < sizeof(quint32))
			return; // not enough bytes for a size of packet

		socket().read((char*)&i_packetSize, sizeof(quint32));

		readyRead(); // recall necessary if all arrived in one block (size + data)
	}
	else
	{
		if(socket().bytesAvailable() < i_packetSize)
			return; // not enough bytes for the packet

		QByteArray packet(i_packetSize, Qt::Uninitialized);
		socket().read(packet.data(), i_packetSize);
		i_packetSize = 0;

		readPacket(packet);

		readyRead();
	}
}

void NetworkTalker::readPacket(QByteArray& data)
{
	readEvent(data);
}

void NetworkTalker::sendPacket(const QByteArray& data)
{
	quint32 packetSize = data.size();

	socket().write((char*)&packetSize, sizeof(quint32));
	socket().write(data.data(), packetSize);
}

void NetworkTalker::readEvent(QByteArray& data)
{
	QDataStream in(&data, QIODevice::ReadOnly);
	EventId eventType;
	in >> *reinterpret_cast<quint32*>(&eventType);

	BaseEvent* event;

	switch(eventType)
	{
	case BaseEventId:
		event = new BaseEvent(eventType, in);
		break;
	case WorldEventId:
		event = new WorldEvent(eventType, in);
		break;
	case ChunkEventId:
		event = new ChunkEvent(eventType, in);
		break;
	case PlayerEventId:
	case PlayerDropEventId:
		event = new PlayerEvent(eventType, in);
		break;
	case InventoryChangedEventId:
		event = new InventoryChangedEvent(eventType, in);
		break;
	case ToolSelectEventId:
		event = new ToolSelectEvent(eventType, in);
		break;
	case PlayerChunkEventId:
	case Connect_PlayerChunkEventId:
	case Disconnect_PlayerChunkEventId:
		event = new PlayerChunkEvent(eventType, in);
		break;
	case BlockEventId:
		event = new BlockEvent(eventType, in);
		break;
	case BlockChangedEventId:
		event = new BlockChangedEvent(eventType, in);
		break;
	case PlayerBlockEventId:
	case Pick_PlayerBlockEventId:
	case Place_PlayerBlockEventId:
		event = new PlayerBlockEvent(eventType, in);
		break;
	}

	processReadEvent(event);
}

void NetworkTalker::sendEvent(BaseEvent* event)
{
	QByteArray packet;
	QDataStream out(&packet, QIODevice::WriteOnly);
	out << (quint32)event->type();
	event->serializeTo(out);
	sendPacket(packet);
}
