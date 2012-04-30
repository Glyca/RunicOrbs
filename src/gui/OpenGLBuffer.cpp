#include "OpenGLBuffer.h"
#include "Log.h"

#define BUFFER_OFFSET(a) ((char*)NULL + (a))
#define BUFFER_OFFSET_FLOAT(a) (BUFFER_OFFSET(a * sizeof(GLfloat)))

/*! 3 floats used to describe vectors or textures coordinates in the .obj loader */
struct ThreeGLfloats {
	GLfloat x, y, z;
};

/*! A face described with "f" in .obj file */
struct ReadedFace {
	GLuint geometry1, normal1, texture1;
	GLuint geometry2, normal2, texture2;
	GLuint geometry3, normal3, texture3; // only if we have 3 vertex or more
	GLuint geometry4, normal4, texture4; // only if we have 4 vertex
};

OpenGLBuffer::OpenGLBuffer(GLenum primitiveType) : m_primitiveType(primitiveType), b_allocated(false), b_dirty(true), i_vertexBufferId(0), i_indicesBufferId(0)
{
}

OpenGLBuffer::OpenGLBuffer(const QString& filename)
{
	QFile file(filename);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		lerror(Channel_OpenGL, "Can't open OBJ file " + file.fileName());
		return;
	}

	QTextStream in(&file);
	int numberOfVertexPerFace = 0; // Determine whether we draw lines, triangles or quads
	std::vector<ThreeGLfloats> vertexGeometry;
	std::vector<ThreeGLfloats> vertexTexture;
	std::vector<ThreeGLfloats> vertexNormal;
	std::vector<ReadedFace> readedFaces;

	while (!in.atEnd()) { // Read each line of the OBJ file
		QString line = in.readLine();
		QTextStream lineIn(&line);

		QString identifier = "";
		lineIn >> identifier;

		if(identifier == "#") // Comment
		{

		}
		else if(identifier == "v") // Parse vertex
		{
			ThreeGLfloats vertex;
			lineIn >> vertex.x;
			lineIn >> vertex.y;
			lineIn >> vertex.z;
			vertexGeometry.push_back(vertex);
		}
		else if(identifier == "vt") // Parse vertex texture
		{
			ThreeGLfloats vertex;
			lineIn >> vertex.x;
			lineIn >> vertex.y;
			// Don't care of the z component for textures
			vertexTexture.push_back(vertex);
		}
		else if(identifier == "vn") // Parse vertex normal
		{
			ThreeGLfloats vertex;
			lineIn >> vertex.x;
			lineIn >> vertex.y;
			lineIn >> vertex.z;
			vertexNormal.push_back(vertex);
		}
		else if(identifier == "f") // Parse a face
		{
			QStringList faceStrings = line.split(' ', QString::SkipEmptyParts);
			// for example if we had the line "f 2/1 1/2 5/3" we now have 4 strings, "f" included
			faceStrings.pop_front(); // Take rid of the "f"

			if(numberOfVertexPerFace == 0) // if == 0, this is the first face we meet, so we decide the type of our VBO
			{
				numberOfVertexPerFace = faceStrings.size();

				/*switch(numberOfVertexPerFace) {
				case 2:
					m_primitiveType = GL_LINES;
					break;
				case 3:
					m_primitiveType = GL_TRIANGLES;
					break;
				case 4:*/
					m_primitiveType = GL_QUADS;
					/*break;
				}*/
			}

			// Alright, read this line and put it in the structure
			ReadedFace readedFace;
			QStringList vertexComponents;

			vertexComponents = faceStrings.at(0).split('/', QString::KeepEmptyParts);
			readedFace.geometry1 = vertexComponents.at(0).toUInt();
			readedFace.texture1 = vertexComponents.at(1).toUInt();
			if(vertexComponents.size() == 3) { // If we have 3 components (like 1/2/3), it means we have a normal
				readedFace.normal1 = vertexComponents.at(2).toUInt();
			}

			vertexComponents = faceStrings.at(1).split('/', QString::KeepEmptyParts);
			readedFace.geometry2 = vertexComponents.at(0).toUInt();
			readedFace.texture2 = vertexComponents.at(1).toUInt();
			if(vertexComponents.size() == 3) { // If we have 3 components (like 1/2/3), it means we have a normal
				readedFace.normal2 = vertexComponents.at(2).toUInt();
			}

			if(faceStrings.size() >= 3) {
				vertexComponents = faceStrings.at(2).split('/', QString::KeepEmptyParts);
				readedFace.geometry3 = vertexComponents.at(0).toUInt();
				readedFace.texture3 = vertexComponents.at(1).toUInt();
				if(vertexComponents.size() == 3) { // If we have 3 components (like 1/2/3), it means we have a normal
					readedFace.normal3 = vertexComponents.at(2).toUInt();
				}

				// If it is a quad
				if(faceStrings.size() == 4) {
					vertexComponents = faceStrings.at(3).split('/', QString::KeepEmptyParts);
					readedFace.geometry4 = vertexComponents.at(0).toUInt();
					readedFace.texture4 = vertexComponents.at(1).toUInt();
					if(vertexComponents.size() == 3) { // If we have 3 components (like 1/2/3), it means we have a normal
						readedFace.normal4 = vertexComponents.at(2).toUInt();
					}
				}
				else // Transform the triangle into a quad
				{
					readedFace.geometry4 = vertexComponents.at(0).toUInt();
					readedFace.texture4 = vertexComponents.at(1).toUInt();
					if(vertexComponents.size() == 3) { // If we have 3 components (like 1/2/3), it means we have a normal
						readedFace.normal4 = vertexComponents.at(2).toUInt();
					}
				}
			}

			// We put our just readed face line in the array
			readedFaces.push_back(readedFace);
		}
	}

	file.close(); // Finish him!

	// Fill our buffer (in ram)
	int numberOfFaces = readedFaces.size();
	for(int i = 0; i < numberOfFaces; ++i) // For all our faces
	{
		OpenGLVertice vertice;

		vertice.vx = vertexGeometry.at(readedFaces.at(i).geometry1 - 1).x;
		vertice.vy = vertexGeometry.at(readedFaces.at(i).geometry1 - 1).y;
		vertice.vz = vertexGeometry.at(readedFaces.at(i).geometry1 - 1).z;

		vertice.tx = vertexTexture.at(readedFaces.at(i).texture1 - 1).x;
		vertice.ty = vertexTexture.at(readedFaces.at(i).texture1 - 1).y;
		/*
		vertice.nx = vertexNormal.at(readedFaces.at(i).normal1 - 1).x;
		vertice.ny = vertexNormal.at(readedFaces.at(i).normal1 - 1).y;
		vertice.nz = vertexNormal.at(readedFaces.at(i).normal1 - 1).z;*/

		addVertice(vertice);

		vertice.vx = vertexGeometry.at(readedFaces.at(i).geometry2 - 1).x;
		vertice.vy = vertexGeometry.at(readedFaces.at(i).geometry2 - 1).y;
		vertice.vz = vertexGeometry.at(readedFaces.at(i).geometry2 - 1).z;

		vertice.tx = vertexTexture.at(readedFaces.at(i).texture2 - 1).x;
		vertice.ty = vertexTexture.at(readedFaces.at(i).texture2 - 1).y;
		/*
		vertice.nx = vertexNormal.at(readedFaces.at(i).normal2 - 1).x;
		vertice.ny = vertexNormal.at(readedFaces.at(i).normal2 - 1).y;
		vertice.nz = vertexNormal.at(readedFaces.at(i).normal2 - 1).z;*/

		addVertice(vertice);

		if(numberOfVertexPerFace >= 3) {

			vertice.vx = vertexGeometry.at(readedFaces.at(i).geometry3 - 1).x;
			vertice.vy = vertexGeometry.at(readedFaces.at(i).geometry3 - 1).y;
			vertice.vz = vertexGeometry.at(readedFaces.at(i).geometry3 - 1).z;

			vertice.tx = vertexTexture.at(readedFaces.at(i).texture3 - 1).x;
			vertice.ty = vertexTexture.at(readedFaces.at(i).texture3 - 1).y;
			/*
			vertice.nx = vertexNormal.at(readedFaces.at(i).normal3 - 1).x;
			vertice.ny = vertexNormal.at(readedFaces.at(i).normal3 - 1).y;
			vertice.nz = vertexNormal.at(readedFaces.at(i).normal3 - 1).z;*/

			addVertice(vertice);

			if(numberOfVertexPerFace == 4) {
				vertice.vx = vertexGeometry.at(readedFaces.at(i).geometry4 - 1).x;
				vertice.vy = vertexGeometry.at(readedFaces.at(i).geometry4 - 1).y;
				vertice.vz = vertexGeometry.at(readedFaces.at(i).geometry4 - 1).z;

				vertice.tx = vertexTexture.at(readedFaces.at(i).texture4 - 1).x;
				vertice.ty = vertexTexture.at(readedFaces.at(i).texture4 - 1).y;
				/*
				vertice.nx = vertexNormal.at(readedFaces.at(i).normal4 - 1).x;
				vertice.ny = vertexNormal.at(readedFaces.at(i).normal4 - 1).y;
				vertice.nz = vertexNormal.at(readedFaces.at(i).normal4 - 1).z;*/

				addVertice(vertice);
			}
		}
	}

}

OpenGLBuffer::~OpenGLBuffer()
{
	clear();
	deleteBuffer();
}

void OpenGLBuffer::genBuffer()
{
	deleteBuffer();
	glGenBuffers(1, &i_vertexBufferId);
	glGenBuffers(1, &i_indicesBufferId);
	b_allocated = true;
}

void OpenGLBuffer::deleteBuffer()
{
	if(b_allocated) {
		glDeleteBuffers(1, &i_vertexBufferId);
		glDeleteBuffers(1, &i_indicesBufferId);
		b_allocated = false;
	}
}

void OpenGLBuffer::addVertice(const OpenGLVertice& vertice)
{
	m_vertex.push_back(vertice);
	m_indices.push_back(m_indices.size());
	b_dirty = true;
}

void OpenGLBuffer::addVertices(const OpenGLVertice& v1, const OpenGLVertice& v2)
{
	addVertice(v1); addVertice(v2);
}

void OpenGLBuffer::addVertices(const OpenGLVertice& v1, const OpenGLVertice& v2, const OpenGLVertice& v3, const OpenGLVertice& v4)
{
	addVertice(v1); addVertice(v2);
	addVertice(v3); addVertice(v4);
}

void OpenGLBuffer::append(const OpenGLBuffer& otherBuffer)
{
	int otherVertexSize = otherBuffer.m_vertex.size();
	for(int i = 0; i < otherVertexSize; ++i) {
		addVertice(otherBuffer.m_vertex.at(i));
	}
}

void OpenGLBuffer::translate3f(const GLfloat tx, const GLfloat ty, const GLfloat tz)
{
	int vertexSize = m_vertex.size();
	for(int i = 0; i < vertexSize; ++i)
	{
		m_vertex.at(i).vx += tx;
		m_vertex.at(i).vy += ty;
		m_vertex.at(i).vz += tz;
	}
}

void OpenGLBuffer::render()
{
	if(b_allocated) {
		if(b_dirty) {
			fill();
		}

		glBindBuffer(GL_ARRAY_BUFFER, i_vertexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_indicesBufferId);

		glVertexPointer(3, // Coordinates per vertex
						GL_FLOAT, // Data type
						8*sizeof(GLfloat), // Offset between each vertice
						BUFFER_OFFSET_FLOAT(0)); // where is the first vertice


		glColorPointer(3, // Coordinates per color
					   GL_FLOAT, // Data type
					   8*sizeof(GLfloat), // Offset between each color
					   BUFFER_OFFSET_FLOAT(3)); // where is the first color

		glTexCoordPointer(2, // Coordinates per texture coordinate
						  GL_FLOAT, // Data type
						  8*sizeof(GLfloat), // Offset between each texture coordinate
						  BUFFER_OFFSET_FLOAT(6)); // where is the first texture coordinate

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		// Render !
		glDrawElements(m_primitiveType, m_indices.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		// Safely disbale buffers (for other compenents of the program)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void OpenGLBuffer::clear()
{
	m_vertex.clear();
	m_indices.clear();
	b_dirty = true;
}

void OpenGLBuffer::fill()
{
	glBindBuffer(GL_ARRAY_BUFFER, i_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_vertex.size() * OPENGLVERTICE_SIZE * sizeof(GLfloat), &m_vertex[0], GL_STATIC_DRAW); // Send data
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Safely disbale buffer

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_indicesBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW); // Send data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Safely disbale buffer

	b_dirty = false;
}
