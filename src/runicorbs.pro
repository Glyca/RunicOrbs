#-------------------------------------------------
#
# Project created by QtCreator 2011-05-22T14:37:41
#
#-------------------------------------------------

QT       += core gui opengl network xml webkit

CONFIG(debug, debug|release) {
        TARGET = ../runicorbsd
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
        LocalServerConnector.cpp \
        RemoteServerConnector.cpp \
        ChunkGenerator.cpp \
        ClientConfiguration.cpp \
        Log.cpp \
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
    Inventory.cpp

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
    Inventory.h

FORMS    += \
        gui/ui/ConnectDialog.ui \
        gui/ui/OptionsDialog.ui \
        gui/ui/ServerWidget.ui \
        gui/ui/Home.ui

OTHER_FILES += ../README.md

# Add translations here (in the UTF-8 format)
TRANSLATIONS = ../lang/craftux_fr.ts

CODECFORTR = UTF-8

# Now necessary for glu*() calls
LIBS += -lGLU

QMAKE_CXXFLAGS_RELEASE -= -g -O2
QMAKE_LFLAGS_RELEASE -= -Wl,-O1
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE += -Wl,-O3 -O3

# Enable this if you compile for yourself (will tune code for your cpu)
#QMAKE_CXXFLAGS += -march=native -mtune=native

# Enable to check size of functions and ASM
#QMAKE_CXXFLAGS += -save-temps -fverbose-asm
#QMAKE_LFLAGS = -Wl,-Map,craftux.map

# Enable this in order to profile the code with callgrind
#QMAKE_CXXFLAGS += -g
