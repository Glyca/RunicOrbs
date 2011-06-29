#-------------------------------------------------
#
# Project created by QtCreator 2011-05-22T14:37:41
#
#-------------------------------------------------

QT       += core gui opengl

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
    Point.cpp \
    Vector3.cpp \
    WorldBlocks.cpp \
    glextensions.cpp

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
    Point.h \
    Vector3.h \
    PhysicSize.h \
    WorldBlocks.h \
    glextensions.h

FORMS    += CraftuxHome.ui

CONFIG += console

DEFINES += GL_GLEXT_PROTOTYPES

# Permet d'voir les traductions en UTF-8
CODECFORTR = UTF-8
# On désactive les infos de déboguage pour le mode release, les crackers n'en ont pas besoin
QMAKE_CXXFLAGS_RELEASE -= -g

