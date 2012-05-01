#include "OpenGLBuffer.h"
#include "Log.h"

#define BUFFER_OFFSET(a) ((char*)NULL + (a))
#define BUFFER_OFFSET_FLOAT(a) (BUFFER_OFFSET(a * sizeof(GLfloat)))
#define BUFFER_OFFSET_UINT(a) (BUFFER_OFFSET(a * sizeof(GLuint)))

/*! 3 floats used to describe vectors or textures coordinates in the .obj loader */
struct FloatVector {
	GLfloat x, y, z;
};

/*! A face described with "f" in .obj file */
struct ReadedFace {
	int numberOfVertex;
	bool haveNormal1, haveNormal2, haveNormal3, haveNormal4;
	GLuint geometry1, normal1, texture1;
	GLuint geometry2, normal2, texture2;
	GLuint geometry3, normal3, texture3; // only if we have 3 vertex or more
	GLuint geometry4, normal4, texture4; // only if we have 4 vertex
};

OpenGLBuffer::OpenGLBuffer(GLenum primitiveType) : b_allocated(false), b_dirty(true), i_vertexBufferId(0), i_indicesBufferId(0)
{
	beginPrimitiveGroup(primitiveType, true);
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
	std::vector<FloatVector> vertexGeometry;
	std::vector<FloatVector> vertexTexture;
	std::vector<FloatVector> vertexNormal;
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
			FloatVector vertex;
			lineIn >> vertex.x;
			lineIn >> vertex.y;
			lineIn >> vertex.z;
			vertexGeometry.push_back(vertex);
		}
		else if(identifier == "vt") // Parse vertex texture
		{
			FloatVector texture;
			lineIn >> texture.x;
			lineIn >> texture.y;
			// Don't care of the z component for textures
			vertexTexture.push_back(texture);
		}
		else if(identifier == "vn") // Parse vertex normal
		{
			FloatVector normal;
			lineIn >> normal.x;
			lineIn >> normal.y;
			lineIn >> normal.z;
			vertexNormal.push_back(normal);
		}
		else if(identifier == "f") // Parse a face
		{
			QStringList faceStrings = line.split(' ', QString::SkipEmptyParts);
			// for example if we had the line "f 2/1 1/2 5/3" we now have 4 strings, "f" included
			faceStrings.pop_front(); // Take rid of the "f"

			// Alright, read this line and put it in the structure
			ReadedFace readedFace;
			QStringList vertexComponents;

			readedFace.numberOfVertex = faceStrings.size();
			readedFace.haveNormal1 = readedFace.haveNormal2 = readedFace.haveNormal3 = readedFace.haveNormal4 = false;

			vertexComponents = faceStrings[0].split('/', QString::KeepEmptyParts);
			readedFace.geometry1 = vertexComponents[0].toUInt();
			readedFace.texture1 = vertexComponents[1].toUInt();
			if(vertexComponents.size() == 3) { // If we have 3 components (like 1/2/3), it means we have a normal
				readedFace.normal1 = vertexComponents[2].toUInt();
				readedFace.haveNormal1 = true;
			}

			vertexComponents = faceStrings[1].split('/', QString::KeepEmptyParts);
			readedFace.geometry2 = vertexComponents[0].toUInt();
			readedFace.texture2 = vertexComponents[1].toUInt();
			if(vertexComponents.size() == 3) { // If we have 3 components (like 1/2/3), it means we have a normal
				readedFace.normal2 = vertexComponents[2].toUInt();
				readedFace.haveNormal2 = true;
			}

			if(readedFace.numberOfVertex >= 3) {
				vertexComponents = faceStrings[2].split('/', QString::KeepEmptyParts);
				readedFace.geometry3 = vertexComponents[0].toUInt();
				readedFace.texture3 = vertexComponents[1].toUInt();
				if(vertexComponents.size() == 3) { // If we have 3 components (like 1/2/3), it means we have a normal
					readedFace.normal3 = vertexComponents[2].toUInt();
					readedFace.haveNormal3 = true;
				}

				// If it is a quad
				if(readedFace.numberOfVertex == 4) {
					vertexComponents = faceStrings[3].split('/', QString::KeepEmptyParts);
					readedFace.geometry4 = vertexComponents[0].toUInt();
					readedFace.texture4 = vertexComponents[1].toUInt();
					if(vertexComponents.size() == 3) { // If we have 3 components (like 1/2/3), it means we have a normal
						readedFace.normal4 = vertexComponents[2].toUInt();
						readedFace.haveNormal4 = true;
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
		ReadedFace& currentFace = readedFaces[i];

		switch(currentFace.numberOfVertex)
		{ // Check how many vertex we have in this face
		case 2:
			beginPrimitiveGroup(GL_LINES);
			break;
		case 3:
			beginPrimitiveGroup(GL_TRIANGLES);
			break;
		case 4:
			beginPrimitiveGroup(GL_QUADS);
			break;
		}

		vertice.vx = vertexGeometry[currentFace.geometry1 - 1].x;
		vertice.vy = vertexGeometry[currentFace.geometry1 - 1].y;
		vertice.vz = vertexGeometry[currentFace.geometry1 - 1].z;

		vertice.tu = vertexTexture[currentFace.texture1 - 1].x;
		vertice.tv = 1.0f - vertexTexture[currentFace.texture1 - 1].y;

		if(currentFace.haveNormal1) {
			vertice.nx = vertexNormal[currentFace.normal1 - 1].x;
			vertice.ny = vertexNormal[currentFace.normal1 - 1].y;
			vertice.nz = vertexNormal[currentFace.normal1 - 1].z;
		}

		vertice.setColors(1.0f);
		addVertice(vertice);

		vertice.vx = vertexGeometry[currentFace.geometry2 - 1].x;
		vertice.vy = vertexGeometry[currentFace.geometry2 - 1].y;
		vertice.vz = vertexGeometry[currentFace.geometry2 - 1].z;

		vertice.tu = vertexTexture[currentFace.texture2 - 1].x;
		vertice.tv = 1.0f - vertexTexture[currentFace.texture2 - 1].y;

		if(currentFace.haveNormal2) {
			vertice.nx = vertexNormal[currentFace.normal2 - 1].x;
			vertice.ny = vertexNormal[currentFace.normal2 - 1].y;
			vertice.nz = vertexNormal[currentFace.normal2 - 1].z;
		}

		vertice.setColors(1.0f);
		addVertice(vertice);

		if(currentFace.numberOfVertex >= 3) {
			vertice.vx = vertexGeometry[currentFace.geometry3 - 1].x;
			vertice.vy = vertexGeometry[currentFace.geometry3 - 1].y;
			vertice.vz = vertexGeometry[currentFace.geometry3 - 1].z;

			vertice.tu = vertexTexture[currentFace.texture3 - 1].x;
			vertice.tv = 1.0f - vertexTexture[currentFace.texture3 - 1].y;

			if(currentFace.haveNormal3) {
				vertice.nx = vertexNormal[currentFace.normal3 - 1].x;
				vertice.ny = vertexNormal[currentFace.normal3 - 1].y;
				vertice.nz = vertexNormal[currentFace.normal3 - 1].z;
			}

			vertice.setColors(1.0f);
			addVertice(vertice);

			if(currentFace.numberOfVertex == 4) {
				vertice.vx = vertexGeometry[currentFace.geometry4 - 1].x;
				vertice.vy = vertexGeometry[currentFace.geometry4 - 1].y;
				vertice.vz = vertexGeometry[currentFace.geometry4 - 1].z;

				vertice.tu = vertexTexture[currentFace.texture4 - 1].x;
				vertice.tv = 1.0f - vertexTexture[currentFace.texture4 - 1].y;

				if(currentFace.haveNormal4) {
					vertice.nx = vertexNormal[currentFace.normal4 - 1].x;
					vertice.ny = vertexNormal[currentFace.normal4 - 1].y;
					vertice.nz = vertexNormal[currentFace.normal4 - 1].z;
				}

				vertice.setColors(1.0f);
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

void OpenGLBuffer::beginPrimitiveGroup(GLenum primitiveType, bool force)
{
	if(m_currentPrimitiveType != primitiveType || force) {
		PrimitiveGroup newPrimitiveGroup;
		newPrimitiveGroup.beginningIndiceIndex = m_indices.size();
		newPrimitiveGroup.primitiveType = primitiveType;
		m_currentPrimitiveType = primitiveType;
		m_primitiveGroups.push_back(newPrimitiveGroup);
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
	GLenum originalPrimitiveType = m_currentPrimitiveType;

	int otherPrimitiveGroupsSize = otherBuffer.m_primitiveGroups.size();
	for(int i = 0; i < otherPrimitiveGroupsSize; ++i) {
		int numberOfIndicesForThisGroup;

		if(i == otherPrimitiveGroupsSize - 1) { // The last group : last index - beginning index
			numberOfIndicesForThisGroup = otherBuffer.m_indices.size() - otherBuffer.m_primitiveGroups[i].beginningIndiceIndex;
		}
		else { // Not the last group : next beginning index - beginning index
			numberOfIndicesForThisGroup = otherBuffer.m_primitiveGroups[i+1].beginningIndiceIndex - otherBuffer.m_primitiveGroups[i].beginningIndiceIndex;
		}

		beginPrimitiveGroup(otherBuffer.m_primitiveGroups[i].primitiveType);
		for(int j = 0; j < numberOfIndicesForThisGroup; ++j) {
			addVertice(otherBuffer.m_vertex[j]);
		}
	}

	beginPrimitiveGroup(originalPrimitiveType, true);
}

void OpenGLBuffer::adjustTextures(const QRectF& targetRectangle)
{
	int numberOfVertex = m_vertex.size();
	for(int i = 0; i < numberOfVertex; ++i)
	{
		m_vertex[i].tu = targetRectangle.x() + m_vertex[i].tu * targetRectangle.width();
		m_vertex[i].tv = targetRectangle.y() + m_vertex[i].tv * targetRectangle.height();
	}
}

void OpenGLBuffer::translate3f(const GLfloat tx, const GLfloat ty, const GLfloat tz)
{
	int vertexSize = m_vertex.size();
	for(int i = 0; i < vertexSize; ++i)
	{
		m_vertex[i].vx += tx;
		m_vertex[i].vy += ty;
		m_vertex[i].vz += tz;
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
						OPENGLVERTICE_SIZE * sizeof(GLfloat), // Offset between each vertice
						BUFFER_OFFSET_FLOAT(0)); // where is the first vertice


		glColorPointer(3, // Coordinates per color
					   GL_FLOAT, // Data type
					   OPENGLVERTICE_SIZE * sizeof(GLfloat), // Offset between each color
					   BUFFER_OFFSET_FLOAT(3)); // where is the first color

		glTexCoordPointer(2, // Coordinates per texture coordinate
						  GL_FLOAT, // Data type
						  OPENGLVERTICE_SIZE * sizeof(GLfloat), // Offset between each texture coordinate
						  BUFFER_OFFSET_FLOAT(6)); // where is the first texture coordinate

		glNormalPointer(GL_FLOAT, // Data type
						OPENGLVERTICE_SIZE * sizeof(GLfloat), // Offset between each texture coordinate
						BUFFER_OFFSET_FLOAT(8)); // where is the first texture coordinate

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		// Render !
		int numberOfPrimitiveGroups = m_primitiveGroups.size();
		for(int i = 0; i < numberOfPrimitiveGroups; ++i)
		{
			int numberOfIndicesForThisGroup;
			if(i == numberOfPrimitiveGroups - 1) { // The last group : last index - beginning index
				numberOfIndicesForThisGroup = m_indices.size() - m_primitiveGroups[i].beginningIndiceIndex;
			}
			else { // Not the last group : next beginning index - beginning index
				numberOfIndicesForThisGroup = m_primitiveGroups[i+1].beginningIndiceIndex - m_primitiveGroups[i].beginningIndiceIndex;
			}

			glDrawElements(m_primitiveGroups[i].primitiveType, numberOfIndicesForThisGroup,
						   GL_UNSIGNED_INT, BUFFER_OFFSET_UINT(m_primitiveGroups[i].beginningIndiceIndex));

		}

		glDisableClientState(GL_NORMAL_ARRAY);
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
	m_primitiveGroups.clear();
	// Keep the primitive type of the buffer by forcing re-creation a primitive group
	beginPrimitiveGroup(m_currentPrimitiveType, true);
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
