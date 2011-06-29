#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GLWidget.h"
#include "BlockInfo.h"
#include "glCamera.h"
#include "PhysicObject.h"

const int WORLD_SIZE_X = 20;
const int WORLD_SIZE_Y = 50;
const int WORLD_SIZE_Z = 20;
const int WORLD_SEA_LEVEL = 5;

class MainWindow : public GLWidget
{
 Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
    /*virtual void initializeOverlayGL();
    virtual void resizeOverlayGL(int w, int h);
    virtual void paintOverlayGL();*/
    void paintEventprout(QPaintEvent *paintEvent);
    virtual void keyPressEvent(QKeyEvent *keyEvent);
    virtual void keyReleaseEvent(QKeyEvent *keyEvent);
    virtual void mouseMoveEvent(QMouseEvent * mouseEvent);

private slots:

    void secondTimerProcess(void);

private:

    void resizeGLreally();
    void drawInfos();
    void fillBlocks();
    void renderBlocks();

    // Test
    void toggleLighting(void);
    void toggleTexture(void);

    bool b_lightingEnabled;
    bool b_textureEnabled;
    bool b_infosEnabled;
    bool b_nowPlaying;
    int i_fpsCount;
    int i_lastFpsCount;
    int i_theQuadRotation;

    // Caméra
    glCamera glc_camera;
    float f_cameraAngle;
    int i_winheight, i_winwidth;

    // Personnage
    PhysicObject po_character;
    float f_charX, f_charY, f_charZ; // Position
    float f_charVX, f_charVY, f_charVZ; // Vitesse

    BlockInfo* world[WORLD_SIZE_X][WORLD_SIZE_Y][WORLD_SIZE_Z];

    // Timers
    QTimer* t_jump;
    QTimer* t_secondTimer;

    // Textures
    GLuint glt_Rock;
    GLuint glt_Dirt;

    // Curseur original
    QCursor m_originalCursor;

};

#endif // MAINWINDOW_H
