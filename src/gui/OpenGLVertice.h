#ifndef OPENGLVERTICE_H
#define OPENGLVERTICE_H

#include "OpenGL.h"

const int OPENGLVERTICE_SIZE = 8; //!< How many floats do we have in each vertice

/*! A vertice that can be put in a OpenGLBuffer */
struct OpenGLVertice
{
	OpenGLVertice(GLfloat vx = 0.0f, GLfloat vy = 0.0f, GLfloat vz = 0.0f, GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat tx = 0.0f, GLfloat ty = 0.0f)
		: vx(vx), vy(vy), vz(vz), r(r), g(g), b(b), tx(tx), ty(ty) {}

	inline void setColors(GLfloat x) {r = x; g = x; b = x;}
	inline void setTextures(GLfloat x, GLfloat y) {tx = x; ty = y;}

	GLfloat vx; //!< Vertice x position
	GLfloat vy; //!< Vertice y position
	GLfloat vz; //!< Vertice z position
	GLfloat r; //!< Color value for red
	GLfloat g; //!< Color value for green
	GLfloat b; //!< Color value for blue
	GLfloat tx; //!< Texture x coordinate
	GLfloat ty; //!< Texture y coordinate
};

#endif // OPENGLVERTICE_H
