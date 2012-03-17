#-------------------------------------------------
#
# Project created by QtCreator 2011-05-22T14:37:41
#
#-------------------------------------------------

QT       += core gui opengl network xml

TARGET = craftux
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
	server/LocalServer.cpp

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
	server/LocalServer.h

FORMS    += \
	gui/CraftuxHome.ui \
	gui/OptionsDialog.ui \
	gui/ServerWidget.ui

# Permet d'voir les traductions en UTF-8
CODECFORTR = UTF-8
# On dsactive les infos de dboguage pour le mode release, les crackers n'en ont pas besoin
QMAKE_CXXFLAGS_RELEASE -= -g
#QMAKE_CXXFLAGS += -save-temps -fverbose-asm
#QMAKE_LFLAGS = -Wl,-O3 -Wl,-Map,craftux.map

OTHER_FILES += ../README.md
