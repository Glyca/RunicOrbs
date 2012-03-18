#include "TextureManager.h"
#include "blocks/Blocks.h"
#include <QtGlobal>

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

QImage TextureManager::getTextureAtlas()
{
	const char* TEXTURE_PATH = "/gfx/textures/";
	QString errorString = QObject::tr("Texture [%1] load failed!");

	// open stone texture
	QString stoneFilename(qApp->applicationDirPath() + TEXTURE_PATH + "stone.png");
	QImage qim_stoneImage(stoneFilename);
	if(qim_stoneImage.isNull())
	{
		qDebug() << errorString.arg(stoneFilename);
	}
	else
	{
		// open dirt texture
		QString dirtFilename(qApp->applicationDirPath() + TEXTURE_PATH + "dirt.png");
		QImage qim_dirtImage(dirtFilename);

		if(qim_dirtImage.isNull())
		{
			qDebug() << errorString.arg(dirtFilename);
		}
		else
		{
			QImage qim_atlas(qim_stoneImage.width(), qim_stoneImage.height() + qim_dirtImage.height(), QImage::Format_ARGB32);
			QPainter qp_assembler(&qim_atlas);
			qp_assembler.drawImage(0, 0, qim_stoneImage, 0, 0, qim_stoneImage.width(), qim_stoneImage.height());
			qp_assembler.drawImage(0, qim_stoneImage.height(), qim_dirtImage, 0, 0, qim_dirtImage.width(), qim_dirtImage.height());
			qp_assembler.end();

			return qim_atlas;
		}
	}
	return QImage();
}

GLuint TextureManager::loadTextures()
{
	QImage qim_textureAtlas = getTextureAtlas();
	if(qim_textureAtlas.isNull())
	{
		qFatal("Can't load textures!");
		return 0;
	}
	else
	{
		QImage qim_Texture = QGLWidget::convertToGLFormat(qim_textureAtlas);

		// Demandons un ID de texture libre
		glGenTextures(1, &gi_textureID);
		// Bindons cet ID
		glBindTexture(GL_TEXTURE_2D, gi_textureID);
		// Filtrage lorsqu'on rétrécit la texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// Filtrage lorsqu'on étire la texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Infos : http://gregs-blog.com/2008/01/17/opengl-texture-filter-parameters-explained/

		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, qim_Texture.width(), qim_Texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, qim_Texture.bits());

		Blocks::STONE.setTexture(TexCoords(0, 0.5),
								 TexCoords(1, 0.5),
								 TexCoords(1, 1),
								 TexCoords(0, 1));
		Blocks::DIRT.setTexture(TexCoords(0, 0),
								TexCoords(1, 0),
								TexCoords(1, 0.5),
								TexCoords(0, 0.5));
		qDebug("Textures loaded!");

		return gi_textureID;
	}
}

void TextureManager::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, gi_textureID);
}

void TextureManager::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
