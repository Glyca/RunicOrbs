#include "Utils.h"
#include "MainWindow.h" // World sizes

CUtils *CUtils::c_Utils = 0;

CUtils::CUtils() : b_cubeListCreated(false), b_axesListCreated(false)
{
    qDebug() << "Gestionaire de display lists construit";
}

CUtils* CUtils::getUtils()
{
    if(c_Utils == 0)
    {
	c_Utils = new CUtils;
    }
    return c_Utils;
}

void CUtils::prepareCube()
{
    gl_cubeList = glGenLists(1);
    glNewList(gl_cubeList, GL_COMPILE);
    drawCube2();
    glEndList();
    b_cubeListCreated = true;
}

void CUtils::fastCube()
{
    if(b_cubeListCreated)
    {
	glCallList(gl_cubeList);
    }
    else
    {
	prepareCube(); fastCube();
    }
}

void CUtils::drawCube()
{
    glBegin(GL_QUADS);
    // Front Face
    glNormal3f( 0.0f, 0.0f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    // Back Face
    glNormal3f( 0.0f, 0.0f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    // Top Face
    glNormal3f( 0.0f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    // Bottom Face
    glNormal3f( 0.0f,-0.5f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    // Right Face
    glNormal3f( 0.5f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    // Left Face
    glNormal3f(-0.5f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();
}

void CUtils::drawCube2()
{
    glBegin(GL_QUADS);
    // Front Face
    glNormal3f( 0.0f, 0.0f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-f_edgeSpace, -f_edgeSpace,  f_edgeSpace);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(f_edgeSpace, -f_edgeSpace,  f_edgeSpace);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(f_edgeSpace, f_edgeSpace, f_edgeSpace);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-f_edgeSpace, f_edgeSpace, f_edgeSpace);
    // Back Face
    glNormal3f( 0.0f, 0.0f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-f_edgeSpace, -f_edgeSpace, -f_edgeSpace);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-f_edgeSpace,f_edgeSpace, -f_edgeSpace);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( f_edgeSpace, f_edgeSpace, -f_edgeSpace);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( f_edgeSpace, -f_edgeSpace, -f_edgeSpace);
    // Top Face
    glNormal3f( 0.0f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-f_edgeSpace, f_edgeSpace, -f_edgeSpace);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-f_edgeSpace, f_edgeSpace,  f_edgeSpace);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(f_edgeSpace, f_edgeSpace,  f_edgeSpace);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(f_edgeSpace, f_edgeSpace, -f_edgeSpace);
    // Bottom Face
    glNormal3f( 0.0f,-0.5f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-f_edgeSpace, -f_edgeSpace, -f_edgeSpace);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(f_edgeSpace, -f_edgeSpace, -f_edgeSpace);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(f_edgeSpace, -f_edgeSpace,  f_edgeSpace);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-f_edgeSpace, -f_edgeSpace,  f_edgeSpace);
    // Right Face
    glNormal3f( 0.5f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(f_edgeSpace, -f_edgeSpace, -f_edgeSpace);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(f_edgeSpace,  f_edgeSpace, -f_edgeSpace);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(f_edgeSpace, f_edgeSpace,  f_edgeSpace);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(f_edgeSpace, -f_edgeSpace,  f_edgeSpace);
    // Left Face
    glNormal3f(-0.5f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-f_edgeSpace, -f_edgeSpace, -f_edgeSpace);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-f_edgeSpace, -f_edgeSpace,  f_edgeSpace);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-f_edgeSpace,  f_edgeSpace,  f_edgeSpace);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-f_edgeSpace, f_edgeSpace, -f_edgeSpace);
    glEnd();
}


// AXES

void CUtils::fastAxes()
{
    if(b_axesListCreated)
    {
	glCallList(gl_axesList);
    }
    else
    {
	prepareAxes(); fastAxes();
    }
}

void CUtils::prepareAxes()
{
    gl_axesList = glGenLists(1);
    glNewList(gl_axesList, GL_COMPILE);
    drawAxes();
    glEndList();
    b_axesListCreated = true;
}

void CUtils::drawAxes()
{
    // Dessin de Ox ROUGE
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(WORLD_SIZE_X*2, 0.0f, 0.0f);
    glEnd();
    // Oy VERT
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, WORLD_SIZE_Y*2, 0.0f);
    glEnd();
    // Oz BLEU
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, WORLD_SIZE_Z*2);
    glEnd();
}

