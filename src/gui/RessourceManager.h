#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "OpenGL.h"

/*! Class which loads various ressources from the disk.
	\warning Textures must be loaded after 3d models. Otherwise textures coordinates of the model will be erroneous because of texture "atlassing". When loading textures in the atlas, texture coordinates of models are adapted.
	\sa RessourceManager::getTextureAtlas() */
class RessourceManager
{
public:
	RessourceManager();
	~RessourceManager();

	/*! Load 3d models contained in .obj files of all blocks */
	void loadModels();

	enum TextureFiltering {
		TextureFiltering_None = 0,
		TextureFiltering_Mipmaps = 1,
		TextureFiltering_BilinearMipmaps = 2,
		TextureFiltering_TrilinearMipmaps = 3
	};

	void setTextureFiltering(TextureFiltering filtering);

	/*! Get a big texture containing all textures */
	QImage getTextureAtlas();

	/*! Load the atlas texture in OpenGL
		\sa getTextureAtlas() */
	GLuint loadTextures();

	void bindTexture(); //!< Bind THE texture
	void unbindTexture(); //!< Unbind any texture binded

	/*! Load items illustrations for the inventory */
	void loadItemImages();

private:
	/*! Give the following power of two (useful to have right texture dimensions) */
	int nextPowerOf2(uint x);

	GLuint gi_textureID; //!< The id of the unique texture, the atlas
	TextureFiltering m_textureFiltering;
};

#endif // TEXTUREMANAGER_H
