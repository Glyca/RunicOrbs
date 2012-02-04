#-------------------------------------------------
#
# Project created by QtCreator 2011-05-22T14:37:41
#
#-------------------------------------------------

QT       += core gui opengl network

TARGET = CrafTuX
TEMPLATE = app

SOURCES += main.cpp\
	CraftuxHome.cpp \
    GLWidget.cpp \
    MainWindow.cpp \
    BlockInfo.cpp \
    PhysicObject.cpp \
    TextureManager.cpp \
    Utils.cpp \
    glQuaternion.cpp \
    glCamera.cpp \
    glVector.cpp \
    glPoint.cpp \
    PhysicEngine.cpp \
    WorldBlocks.cpp \
    glextensions.cpp \
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
    GameWindow.cpp \
    Vector.cpp

HEADERS  += CraftuxHome.h \
    GLWidget.h \
    MainWindow.h \
    BlockInfo.h \
    PhysicObject.h \
    TextureManager.h \
    Utils.h \
    glQuaternion.h \
    glCamera.h \
    glVector.h \
    glPoint.h \
    PhysicEngine.h \
    PhysicSize.h \
    WorldBlocks.h \
    glextensions.h \
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
    GameWindow.h \
    Vector.h

FORMS    += CraftuxHome.ui

DEFINES += GL_GLEXT_PROTOTYPES

# Permet d'voir les traductions en UTF-8
CODECFORTR = UTF-8
# On dsactive les infos de dboguage pour le mode release, les crackers n'en ont pas besoin
QMAKE_CXXFLAGS_RELEASE -= -g
#QMAKE_CXXFLAGS += -save-temps -fverbose-asm

OTHER_FILES += \
    README.md
