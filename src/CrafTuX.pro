#-------------------------------------------------
#
# Project created by QtCreator 2011-05-22T14:37:41
#
#-------------------------------------------------

QT       += core gui opengl network xml

DESTDIR = ../

CONFIG(debug, debug|release) {
	TARGET = craftuxd
} else {
	TARGET = craftux
}

CONFIG += thread

TEMPLATE = app

SOURCES += main.cpp\
	PhysicObject.cpp \
	PhysicEngine.cpp \
	Chunk.cpp \
	World.cpp \
	Entity.cpp \
	Player.cpp \
	Me.cpp \
	ServerConnector.cpp \
	LocalServerConnector.cpp \
	RemoteServerConnector.cpp \
	gui/GameWindow.cpp \
	gui/GLWidget.cpp \
	gui/glextensions.cpp \
	gui/CraftuxHome.cpp \
	gui/TextureManager.cpp \
	gui/ChunkDrawer.cpp \
	ChunkGenerator.cpp \
	gui/OptionsDialog.cpp \
	ClientConfiguration.cpp \
	blocks/BlockInfo.cpp \
	blocks/BlockDescriptor.cpp \
	blocks/Blocks.cpp \
	server/MultiplayerServerThread.cpp \
	server/MultiplayerServer.cpp \
	gui/ServerWidget.cpp \
	server/ClientThread.cpp \
	server/Server.cpp \
	server/LocalServer.cpp \
	server/events/Event.cpp \
	server/events/PlayerEvent.cpp \
	server/events/BlockPickEvent.cpp \
	server/events/BlockUseEvent.cpp \
	server/events/MoveEvent.cpp \
	server/events/ChunkEvent.cpp \
	server/events/ChunkConnectEvent.cpp \
	gui/ConnectDialog.cpp \
	Log.cpp \
	InventorySlot.cpp \
	server/events/SlotSelectEvent.cpp \
	server/events/ServerEvent.cpp \
	server/events/ClientEvent.cpp \
	server/events/InventorySetEvent.cpp

HEADERS  += \
	PhysicObject.h \
	PhysicEngine.h \
	PhysicSize.h \
	Chunk.h \
	World.h \
	Entity.h \
	Player.h \
	Me.h \
	ServerConnector.h \
	LocalServerConnector.h \
	RemoteServerConnector.h \
	Vector.h \
	version.h \
	gui/GameWindow.h \
	gui/GLWidget.h \
	gui/glextensions.h \
	gui/CraftuxHome.h \
	gui/TextureManager.h \
	gui/ChunkDrawer.h \
	ChunkGenerator.h \
	gui/OptionsDialog.h \
	ClientConfiguration.h \
	blocks/BlockInfo.h \
	blocks/BlockDescriptor.h \
	blocks/Blocks.h \
	server/MultiplayerServerThread.h \
	server/MultiplayerServer.h \
	gui/ServerWidget.h \
	server/ClientThread.h \
	server/Server.h \
	server/LocalServer.h \
	gui/OpenGL.h \
	server/events/Event.h \
	server/events/PlayerEvent.h \
	server/events/BlockPickEvent.h \
	server/events/BlockUseEvent.h \
	server/events/MoveEvent.h \
	server/events/ChunkEvent.h \
	server/events/ChunkConnectEvent.h \
	gui/ConnectDialog.h \
	Log.h \
	InventorySlot.h \
	server/events/SlotSelectEvent.h \
	server/events/ServerEvent.h \
	server/events/ClientEvent.h \
	server/events/InventorySetEvent.h

FORMS    += \
	gui/CraftuxHome.ui \
	gui/OptionsDialog.ui \
	gui/ServerWidget.ui \
	gui/ConnectDialog.ui

OTHER_FILES += ../README.md

# Add translations here (in the UTF-8 format)
TRANSLATIONS = ../lang/craftux_fr.ts

CODECFORTR = UTF-8

QMAKE_CXXFLAGS_RELEASE -= -g -O2
QMAKE_LFLAGS_RELEASE -= -Wl,-O1
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE += -Wl,-O3

# Enable this if you compile for yourself (will tune code for your cpu)
#QMAKE_CXXFLAGS += -march=native -mtune=native

# Enable to check size of functions and ASM
#QMAKE_CXXFLAGS += -save-temps -fverbose-asm
#QMAKE_LFLAGS = -Wl,-Map,craftux.map
