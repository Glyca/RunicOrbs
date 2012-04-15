#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QString>
#include "OpenGL.h"

/*! Contains a couple of floats wich represent a texture position on a face */
class TexCoords {
public:
	TexCoords(GLfloat x = 0.0f, GLfloat y = 0.0f) : tx(x), ty(y) {}
	GLfloat tx, ty;
};

/*! Loads all textures and inform the blocks what are their texture coordinates */
class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	enum TextureFiltering {
		TextureFiltering_None = 0,
		TextureFiltering_Bilinear = 1,
		TextureFiltering_BilinearMipmaps = 2,
		TextureFiltering_TrilinearMipmaps = 3
	};

	void setTextureFiltering(TextureFiltering filtering);

	/*! Get a big txture containing all textures */
	QImage getTextureAtlas();

	GLuint loadTextures();

	void bindTexture(); //!< Bind THE texture
	void unbindTexture(); //!< Unbind any texture binded

	/*! Load items illustrations for the inventory */
	void loadItemImages();

private:
	GLuint gi_textureID;
	TextureFiltering m_textureFiltering;
};

#endif // TEXTUREMANAGER_H
