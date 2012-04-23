#-------------------------------------------------
#
# Project created by QtCreator 2011-05-22T14:37:41
#
#-------------------------------------------------

QT       += core gui opengl network xml webkit

CONFIG(debug, debug|release) {
	DESTDIR = ../build/debug/
	RCC_DIR = ../build/debug/rcc/
	UI_DIR = ../build/debug/ui/
	MOC_DIR = ../build/debug/moc/
	OBJECTS_DIR = ../build/debug/obj/
	TARGET = ../../craftuxd
} else {
	DESTDIR = ../build/release/
	RCC_DIR = ../build/release/rcc/
	UI_DIR = ../build/release/ui/
	MOC_DIR = ../build/release/moc/
	OBJECTS_DIR = ../build/release/obj/
	TARGET = ../../craftux
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
	ChunkGenerator.cpp \
	ClientConfiguration.cpp \
	Log.cpp \
	InventorySlot.cpp \
	blocks/BlockInfo.cpp \
	blocks/BlockDescriptor.cpp \
	blocks/Blocks.cpp \
	server/MultiplayerServerThread.cpp \
	server/MultiplayerServer.cpp \
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
	server/events/SlotSelectEvent.cpp \
	server/events/ServerEvent.cpp \
	server/events/ClientEvent.cpp \
	server/events/InventorySetEvent.cpp \
	gui/GameWindow.cpp \
	gui/GLWidget.cpp \
	gui/glextensions.cpp \
	gui/TextureManager.cpp \
	gui/ChunkDrawer.cpp \
	gui/OpenGLBuffer.cpp \
	gui/OpenGLVertice.cpp \
	gui/ui/ConnectDialog.cpp \
	gui/ui/CraftuxHome.cpp \
	gui/ui/OptionsDialog.cpp \
	gui/ui/ServerWidget.cpp \
	blocks/CubeBlock.cpp \
	blocks/TorchBlock.cpp \

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
	ChunkGenerator.h \
	ClientConfiguration.h \
	Log.h \
	FastMath.h \
	InventorySlot.h \
	blocks/BlockInfo.h \
	blocks/BlockDescriptor.h \
	blocks/Blocks.h \
	server/MultiplayerServerThread.h \
	server/MultiplayerServer.h \
	server/ClientThread.h \
	server/Server.h \
	server/LocalServer.h \
	server/events/Event.h \
	server/events/PlayerEvent.h \
	server/events/BlockPickEvent.h \
	server/events/BlockUseEvent.h \
	server/events/MoveEvent.h \
	server/events/ChunkEvent.h \
	server/events/ChunkConnectEvent.h \
	server/events/SlotSelectEvent.h \
	server/events/ServerEvent.h \
	server/events/ClientEvent.h \
	server/events/InventorySetEvent.h \
	gui/OpenGL.h \
	gui/GameWindow.h \
	gui/GLWidget.h \
	gui/glextensions.h \
	gui/TextureManager.h \
	gui/ChunkDrawer.h \
	gui/ui/ConnectDialog.h \
	gui/ui/CraftuxHome.h \
	gui/ui/OptionsDialog.h \
	gui/ui/ServerWidget.h \
	gui/OpenGLBuffer.h \
	gui/OpenGLVertice.h \
	blocks/CubeBlock.h \
	blocks/TorchBlock.h

FORMS    += \
	gui/ui/ConnectDialog.ui \
	gui/ui/CraftuxHome.ui \
	gui/ui/OptionsDialog.ui \
	gui/ui/ServerWidget.ui

OTHER_FILES += ../README.md

# Add translations here (in the UTF-8 format)
TRANSLATIONS = ../lang/craftux_fr.ts

CODECFORTR = UTF-8

QMAKE_CXXFLAGS_RELEASE -= -g -O2
QMAKE_LFLAGS_RELEASE -= -Wl,-O1
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE += -Wl,-O3 -O3

# Enable this if you compile for yourself (will tune code for your cpu)
#QMAKE_CXXFLAGS += -march=native -mtune=native

# Enable to check size of functions and ASM
#QMAKE_CXXFLAGS += -save-temps -fverbose-asm
#QMAKE_LFLAGS = -Wl,-Map,craftux.map
