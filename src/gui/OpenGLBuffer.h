#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include "OpenGL.h"
#include "OpenGLVertice.h"
#include <vector>

class OpenGLBuffer
{
public:
	/*! The constructor don't allocate anything, you have to do it manually by calling genBuffer() */
	OpenGLBuffer();
	/*! The destructor safely calls deleteBuffer() to free the buffer */
	~OpenGLBuffer();

	/*! Allocates a new OpenGL buffer and delete the old one if it allocated */
	void genBuffer();

	/*! Push a vertice to the buffer */
	void addVertice(const OpenGLVertice& vertice);
	/*! Push 4 vertex to the buffer */
	void addVertices(const OpenGLVertice& v1, const OpenGLVertice& v2, const OpenGLVertice& v3, const OpenGLVertice& v4);

	/*! Render the buffer on the screen */
	void render();

	/*! Clear all vertex of the buffer */
	void clear();

	/*! Safely delete the OpenGL buffer if it is allocated */
	void deleteBuffer();

private:
	/*! Fill the buffer with the data of our vertex */
	void fill();

	std::vector<OpenGLVertice> m_vertex; //!< Vertex of the buffer
	bool b_allocated; //!< Whether the buffer is allocated or not
	bool b_dirty; //!< If we must refill the buffer with the new vertex
	GLuint i_vertexBufferId; //!< OpenGL ID of the VBO
	GLuint i_indicesBufferId; //!< OpenGL ID of the IBO
};

#endif // OPENGLBUFFER_H
