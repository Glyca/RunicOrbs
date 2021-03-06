#-------------------------------------------------
#
# Project created by QtCreator 2011-05-22T14:37:41
#
#-------------------------------------------------

QT       += core gui opengl network xml webkit

CONFIG(debug, debug|release) {
TARGET = ../runicorbsd
CONFIG += debug
} else {
TARGET = ../runicorbs
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
								ChunkGenerator.cpp \
								ClientConfiguration.cpp \
								Log.cpp \
								blocks/BlockInfo.cpp \
								blocks/BlockDescriptor.cpp \
								blocks/Blocks.cpp \
								server/Server.cpp \
								server/LocalServer.cpp \
								gui/GameWindow.cpp \
								gui/GLWidget.cpp \
								gui/glextensions.cpp \
								gui/ChunkDrawer.cpp \
								gui/OpenGLBuffer.cpp \
								gui/OpenGLVertice.cpp \
								gui/ui/ConnectDialog.cpp \
								gui/ui/OptionsDialog.cpp \
								gui/ui/ServerWidget.cpp \
								blocks/CubeBlock.cpp \
								blocks/TorchBlock.cpp \
								gui/ui/Home.cpp \
								gui/RessourceManager.cpp \
				Inventory.cpp \
				server/ServerConfiguration.cpp \
				AbstractConfiguration.cpp \
				server/MultiplayerServer.cpp \
				server/ClientHandler.cpp \
				server/events/BaseEvent.cpp \
				server/events/WorldEvent.cpp \
				server/events/ChunkEvent.cpp \
				EventReadyObject.cpp \
				server/events/BlockEvent.cpp \
				server/events/PlayerEvent.cpp \
				server/events/PlayerChunkEvent.cpp \
				server/events/PlayerBlockEvent.cpp \
				server/events/BlockChangedEvent.cpp \
				server/ClientServer.cpp \
				server/events/InventoryChangedEvent.cpp \
				gui/ui/LoadingWidget.cpp \
	server/events/ToolSelectEvent.cpp \
	server/NetworkTalker.cpp \
    server/events/ChunkNewDataEvent.cpp

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
								Vector.h \
								version.h \
								ChunkGenerator.h \
								ClientConfiguration.h \
								Log.h \
								FastMath.h \
								blocks/BlockInfo.h \
								blocks/BlockDescriptor.h \
								blocks/Blocks.h \
								server/Server.h \
								server/LocalServer.h \
								gui/OpenGL.h \
								gui/GameWindow.h \
								gui/GLWidget.h \
								gui/glextensions.h \
								gui/ChunkDrawer.h \
								gui/ui/ConnectDialog.h \
								gui/ui/OptionsDialog.h \
								gui/ui/ServerWidget.h \
								gui/OpenGLBuffer.h \
								gui/OpenGLVertice.h \
								blocks/CubeBlock.h \
								blocks/TorchBlock.h \
								gui/ui/Home.h \
				gui/RessourceManager.h \
				Inventory.h \
				server/ServerConfiguration.h \
				AbstractConfiguration.h \
				server/MultiplayerServer.h \
				server/ClientHandler.h \
				server/events/BaseEvent.h \
				server/events/EventIds.h \
				server/events/WorldEvent.h \
				server/events/ChunkEvent.h \
				EventReadyObject.h \
				server/events/BlockEvent.h \
				server/events/PlayerEvent.h \
				server/events/PlayerChunkEvent.h \
				server/events/PlayerBlockEvent.h \
				server/events/BlockChangedEvent.h \
				server/ClientServer.h \
				server/events/InventoryChangedEvent.h \
				gui/ui/LoadingWidget.h \
	server/events/ToolSelectEvent.h \
	server/NetworkTalker.h \
    server/events/ChunkNewDataEvent.h

FORMS    += \
								gui/ui/ConnectDialog.ui \
								gui/ui/OptionsDialog.ui \
								gui/ui/ServerWidget.ui \
								gui/ui/Home.ui

OTHER_FILES += ../README.md \
				ressources.rc

# Add translations here (in the UTF-8 format)
TRANSLATIONS = ../lang/fr.ts

CODECFORTR = UTF-8

RC_FILE = ressources.rc

# Now necessary for glu*() calls
unix {
LIBS += -lGLU
}

QMAKE_CXXFLAGS_RELEASE -= -g -O2
QMAKE_LFLAGS_RELEASE -= -Wl,-O1
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE += -Wl,-O3 -O3

# Enable this if you compile for yourself (will tune code for your cpu)
#QMAKE_CXXFLAGS += -march=native -mtune=native

# Enable to check size of functions and ASM
#QMAKE_CXXFLAGS += -save-temps -fverbose-asm
#QMAKE_LFLAGS = -Wl,-Map,runicorbs.map

# Enable this in order to profile the code with callgrind
#QMAKE_CXXFLAGS += -g
