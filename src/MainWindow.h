﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GLWidget.h"
#include "BlockInfo.h"
#include "glCamera.h"
#include "PhysicObject.h"
#include "WorldBlocks.h"

const int WORLD_SIZE_X = 20;
const int WORLD_SIZE_Y = 50;
const int WORLD_SIZE_Z = 20;
const int WORLD_SEA_LEVEL = 5;

class MainWindow : public GLWidget
{
 Q_OBJECT

public:
    explicit MainWindow(WorldBlocks* worldBlocks);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void keyPressEvent(QKeyEvent *keyEvent);
    virtual void keyReleaseEvent(QKeyEvent *keyEvent);
    virtual void mouseMoveEvent(QMouseEvent * mouseEvent);

	WorldBlocks* getWorldBlocksPointer();

private slots:

    void secondTimerProcess(void);

private:

    void drawInfos();
    void renderBlocks();

    // Testing
    void toggleLighting(void);
    void toggleTexture(void);

    bool b_lightingEnabled;
    bool b_textureEnabled;
    bool b_infosEnabled;
    bool b_nowPlaying;
    int i_fpsCount;
    int i_lastFpsCount;

    // OpenGL
    GLvoid* vp_vertexArray;

    // Caméra
    glCamera glc_camera;
    int i_winheight, i_winwidth;

	// Personnage & cube de test
	PhysicObject* po_perso;
	PhysicObject* po_cube;

    // Monde
    WorldBlocks* m_worldBlocks;

    // Timers
    QTimer* t_secondTimer;

    // Textures
    GLuint glt_Rock;
    GLuint glt_Dirt;

    // Curseur original
    QCursor m_originalCursor;

};

#endif // MAINWINDOW_H