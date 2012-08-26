#ifndef EVENTIDS_H
#define EVENTIDS_H

enum EventId {
	BaseEventId = 1000,

	WorldEventId = 2000,

	ChunkEventId = 3000,

	PlayerEventId = 4000,
	PlayerDropEventId = 4000,

	InventoryChangedEventId = 4010,

	ToolSelectEventId = 4020,

	PlayerChunkEventId = 4100,
	Connect_PlayerChunkEventId = 4101,
	Disconnect_PlayerChunkEventId = 4102,

	BlockEventId = 5000,
	BlockChangedEventId = 5001,

	PlayerBlockEventId = 6000,
	Pick_PlayerBlockEventId = 6001,
	Place_PlayerBlockEventId = 6002
};

#endif // EVENTIDS_H
