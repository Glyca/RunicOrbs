#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include "OpenGLVertice.h"
#include <vector>

struct PrimitiveGroup {
	GLuint beginningIndiceIndex; //!< At which index of the indice array the group begins \sa m_indices
	GLenum primitiveType; //!< Which is the king of primitive for this group
};

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

	/*! Begin a group of the same primitive type (like GL_TRIANGLES or GL_QUADS)
		Next calls to addVertice() will render vertices of that primitive
		\sa PrimitiveGroup addVertice() */
	void beginPrimitiveGroup(GLenum primitiveType, bool force = false);

	/*! Push a vertice to the buffer with a new indice */
	void addVertice(const OpenGLVertice& vertice);
	/*! Push 2 vertex to the buffer with new indices for each one */
	void addVertices(const OpenGLVertice& v1, const OpenGLVertice& v2);
	/*! Push 4 vertex to the buffer with new indices for each one */
	void addVertices(const OpenGLVertice& v1, const OpenGLVertice& v2, const OpenGLVertice& v3, const OpenGLVertice& v4);

	/*! Copy otherBuffer at the end of this buffer */
	void append(const OpenGLBuffer& otherBuffer);

	/*! Make texture coordinates be in the targetRectangle instead of in a 1;1 square.
		Used for texture atlas to correct texture coordinates.
		\warning This function must be called only one time! */
	void adjustTextures(const QRectF& targetRectangle);

	/*! Translates the whole buffer */
	void translate3f(const GLfloat tx, const GLfloat ty, const GLfloat tz);

	/*! Render the buffer on the screen */
	void render();

	/*! Avoid any new geometry to be uploaded to the video memory. Used when redrawing a chunk for example */
	void preventUpload(bool preventIt);

	/*! Clear all vertex of the buffer */
	void clear();

	/*! Safely delete the OpenGL buffer if it is allocated */
	void deleteBuffer();

private:
	/*! Upload the data of our vertex to the buffer in video memory */
	void upload();

	GLenum m_currentPrimitiveType; //!< The kind of primitives to draw (mode argument of glDrawElements)
	std::vector<OpenGLVertice> m_vertex; //!< Vertex of the buffer
	std::vector<GLuint> m_indices; //!< Indices of the indice buffer
	std::vector<PrimitiveGroup> m_primitiveGroups;
	bool b_allocated; //!< Whether the buffer is allocated in video memory or not
	bool b_dirty; //!< If we must refill the buffer with the new vertex
	volatile bool b_preventUpload; //!< Whether we can upload geometry to the buffer or not
	GLuint i_vertexBufferId; //!< OpenGL ID of the VBO
	GLuint i_indicesBufferId; //!< OpenGL ID of the IBO
};

#endif // OPENGLBUFFER_H
