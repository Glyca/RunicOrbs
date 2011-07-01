#ifndef UTILS_H
#define UTILS_H

#include <QtOpenGL>

const float f_edgeSpace = 0.5f;

// Singloton class
class CUtils
{
public:
    CUtils();
    ~CUtils();

    static class CUtils* c_Utils;
    static CUtils* getUtils();

    void fastCube();
    void drawCube();
    void drawCube2();

    void fastAxes();

private:
    GLuint gl_cubeList; bool b_cubeListCreated;
    GLuint gl_axesList; bool b_axesListCreated;

    void prepareCube();

    void prepareAxes(); void drawAxes();


};

#define Utils (CUtils::getUtils())

#endif // UTILS_H
