#-------------------------------------------------
#
# Project created by QtCreator 2011-05-22T14:37:41
#
#-------------------------------------------------

QT       += core gui opengl network xml

TARGET = craftux
TEMPLATE = app

SOURCES += main.cpp\
	BlockInfo.cpp \
	PhysicObject.cpp \
	PhysicEngine.cpp \
	Chunk.cpp \
	World.cpp \
	Entity.cpp \
	Player.cpp \
	Me.cpp \
	LocalServer.cpp \
	MultiplayerServer.cpp \
	ServerConnector.cpp \
	LocalServerConnector.cpp \
	RemoteServerConnector.cpp \
	Server.cpp \
	gui/GameWindow.cpp \
	gui/GLWidget.cpp \
	gui/glextensions.cpp \
	gui/CraftuxHome.cpp \
	gui/TextureManager.cpp \
	gui/ChunkDrawer.cpp \
	ChunkGenerator.cpp \
	gui/OptionsDialog.cpp \
	ClientConfiguration.cpp

HEADERS  += \
	BlockInfo.h \
	PhysicObject.h \
	PhysicEngine.h \
	PhysicSize.h \
	Chunk.h \
	World.h \
	Entity.h \
	Player.h \
	Me.h \
	LocalServer.h \
	MultiplayerServer.h \
	ServerConnector.h \
	LocalServerConnector.h \
	RemoteServerConnector.h \
	Server.h \
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
	ClientConfiguration.h

FORMS    += \
	gui/CraftuxHome.ui \
	gui/OptionsDialog.ui

DEFINES += GL_GLEXT_PROTOTYPES

# Permet d'voir les traductions en UTF-8
CODECFORTR = UTF-8
# On dsactive les infos de dboguage pour le mode release, les crackers n'en ont pas besoin
QMAKE_CXXFLAGS_RELEASE -= -g
#QMAKE_CXXFLAGS += -save-temps -fverbose-asm
#QMAKE_LFLAGS = -Wl,-O3 -Wl,-Map,craftux.map

OTHER_FILES += \
	../README.md
