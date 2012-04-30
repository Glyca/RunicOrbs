#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include "OpenGLVertice.h"
#include <vector>

/*! Represents geometry that can be put in an OpenGL Buffer Object */
class OpenGLBuffer
{
public:
	/*! The constructor don't allocate anything, you have to do it manually by calling genBuffer() */
	OpenGLBuffer(GLenum primitiveType);
	/*! Constructs a buffer from a .obj file */
	OpenGLBuffer(const QString& filename);
	/*! The destructor safely calls deleteBuffer() to free the buffer */
	~OpenGLBuffer();

	/*! Allocates a new OpenGL buffer and delete the old one if allocated */
	void genBuffer();

	/*! Push a vertice to the buffer with a new indice */
	void addVertice(const OpenGLVertice& vertice);
	/*! Push 2 vertex to the buffer with new indices for each one */
	void addVertices(const OpenGLVertice& v1, const OpenGLVertice& v2);
	/*! Push 4 vertex to the buffer with new indices for each one */
	void addVertices(const OpenGLVertice& v1, const OpenGLVertice& v2, const OpenGLVertice& v3, const OpenGLVertice& v4);

	/*! Copy otherBuffer at the end of this buffer */
	void append(const OpenGLBuffer& otherBuffer);

	/*! Translates the whole buffer */
	void translate3f(const GLfloat tx, const GLfloat ty, const GLfloat tz);

	/*! Render the buffer on the screen */
	void render();

	/*! Clear all vertex of the buffer */
	void clear();

	/*! Safely delete the OpenGL buffer if it is allocated */
	void deleteBuffer();

private:
	/*! Fill the buffer with the data of our vertex */
	void fill();

	GLenum m_primitiveType; //!< The kind of primitives to draw (mode argument of glDrawElements)
	std::vector<OpenGLVertice> m_vertex; //!< Vertex of the buffer
	std::vector<GLuint> m_indices; //!< Indices of the indice buffer
	bool b_allocated; //!< Whether the buffer is allocated or not
	bool b_dirty; //!< If we must refill the buffer with the new vertex
	GLuint i_vertexBufferId; //!< OpenGL ID of the VBO
	GLuint i_indicesBufferId; //!< OpenGL ID of the IBO
};

#endif // OPENGLBUFFER_H
