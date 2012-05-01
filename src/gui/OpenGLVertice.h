#ifndef OPENGLVERTICE_H
#define OPENGLVERTICE_H

#include "OpenGL.h"

const int OPENGLVERTICE_SIZE = 11; //!< How many floats do we have in each vertice

/*! A vertice that can be put in a OpenGLBuffer (32 bytes) */
struct OpenGLVertice
{
	OpenGLVertice(GLfloat vx = 0.0f, GLfloat vy = 0.0f, GLfloat vz = 0.0f, GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat tx = 0.0f, GLfloat ty = 0.0f, GLfloat nx = 0.0f, GLfloat ny = 0.0f, GLfloat nz = 0.0f)
		: vx(vx), vy(vy), vz(vz), r(r), g(g), b(b), tu(tx), tv(ty), nx(nx), ny(ny), nz(nz) {}

	inline void setColors(GLfloat x) {r = x; g = x; b = x;}
	inline void setTextures(GLfloat x, GLfloat y) {tu = x; tv = y;}
	inline void setNormals(GLfloat n) {nx = ny = nz = n;}

	GLfloat vx; //!< Vertice x position
	GLfloat vy; //!< Vertice y position
	GLfloat vz; //!< Vertice z position

	GLfloat r; //!< Color value for red
	GLfloat g; //!< Color value for green
	GLfloat b; //!< Color value for blue

	GLfloat tu; //!< Texture x coordinate
	GLfloat tv; //!< Texture y coordinate

	GLfloat nx; //!< Normal x position
	GLfloat ny; //!< Normal y position
	GLfloat nz; //!< Normal z position
};

#endif // OPENGLVERTICE_H
