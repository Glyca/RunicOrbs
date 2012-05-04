#include "RessourceManager.h"
#include "blocks/Blocks.h"
#include "blocks/BlockDescriptor.h"
#include "blocks/TorchBlock.h"
#include "Log.h"

const char* TEXTURE_PATH = "/gfx/textures/";
const char* ITEMS_IMAGES_PATH = "/gfx/items/";

RessourceManager::RessourceManager() : m_textureFiltering(TextureFiltering_BilinearMipmaps)
{

}

RessourceManager::~RessourceManager()
{

}

void RessourceManager::loadModels()
{
	// Load all models of blocks
	for(int blockId = 0; blockId < MAX_BLOCKID; ++blockId) {
		Blocks::byId(blockId).loadModel(qApp->applicationDirPath() + TEXTURE_PATH);
	}
}

void RessourceManager::setTextureFiltering(TextureFiltering filtering)
{
	m_textureFiltering = filtering;
}

QImage RessourceManager::getTextureAtlas()
{
	QString errorString = QObject::tr("Texture loading [%1] for \"%2\" failed!");
	QString loadedString = QObject::tr("Successfully loaded \"%1\" texture [%2].");

	QMap<int, QImage> qmap_textureImages;
	int atlasWidth = 0;
	int atlasHeight = 0;

	// Step 1 : Load all our textures and get the size of the final atlas
	// Textures are stacked on the height
	for(int blockID = 1; blockID < MAX_BLOCKID; blockID++)
	{
		QString textureFilename(qApp->applicationDirPath() + TEXTURE_PATH + Blocks::byId(blockID).name() + ".png");
		QImage qim_texture(textureFilename);
		if(qim_texture.isNull()) {
			lwarning(Channel_Textures, errorString.arg(textureFilename, Blocks::byId(blockID).name()));
		}
		else {
			qmap_textureImages.insert(blockID, qim_texture);
			ldebug(Channel_Textures, loadedString.arg(Blocks::byId(blockID).name(), textureFilename));
			// The atlas width is the greater width of all textures
			if(qim_texture.width() > atlasWidth) {
				atlasWidth = qim_texture.width();
			}
			// Since textures are stacked on the height
			atlasHeight += qim_texture.height();
		}
	}

	// Step 2 : Make the atlas dimension be power of two
	atlasWidth = nextPowerOf2(atlasWidth);
	atlasHeight = nextPowerOf2(atlasHeight);

	// Step 3 : Draw the texture atlas, and set texture coordinates of BlockDescriptor properly
	QImage qim_atlas(atlasWidth, atlasHeight, QImage::Format_ARGB32);
	qim_atlas.fill(Qt::transparent);
	QPainter qp_assembler(&qim_atlas);
	int currentHeight = 0;

	QMapIterator<int, QImage> it(qmap_textureImages);
	while (it.hasNext()) {
		it.next();
		qp_assembler.drawImage(0, currentHeight, it.value());

		QRectF textureAtlasPosition(0, // Left
									GLfloat(currentHeight) / GLfloat(atlasHeight), // Top
									GLfloat(it.value().width()) / GLfloat(atlasWidth), // Width
									GLfloat(it.value().height()) / GLfloat(atlasHeight) // Height
									); // It is the position of this block texture in the atlas, to be used in texture coordinates

		Blocks::byId(it.key()).setTexture(textureAtlasPosition, float(it.value().width()) / float(it.value().height()));
		currentHeight += it.value().height();
	}

	qp_assembler.end();
	qim_atlas = qim_atlas.mirrored(false, true); // Flip the texture atlas vertically since OpenGL invert it later.
	return qim_atlas;
}

GLuint RessourceManager::loadTextures()
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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		switch(m_textureFiltering) {
		// Infos : http://gregs-blog.com/2008/01/17/opengl-texture-filter-parameters-explained/
		// http://www.opengl.org/discussion_boards/ubbthreads.php?ubb=showflat&Number=133117
		case TextureFiltering_None:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);// Filtrage lorsqu'on rétrécit la texture
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);// Filtrage lorsqu'on étire la texture
			break;
		case TextureFiltering_Bilinear:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case TextureFiltering_BilinearMipmaps:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case TextureFiltering_TrilinearMipmaps:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		}

		if(m_textureFiltering >= TextureFiltering_BilinearMipmaps) {
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, qim_Texture.width(), qim_Texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, qim_Texture.bits());
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, qim_Texture.width(), qim_Texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, qim_Texture.bits());
		}

		linfo(Channel_Textures, QObject::tr("Textures loaded!"));

		return gi_textureID;
	}
}

void RessourceManager::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, gi_textureID);
}

void RessourceManager::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RessourceManager::loadItemImages()
{
	QString errorString = QObject::tr("Item image loading [%1] for \"%2\" failed!");
	QString loadedString = QObject::tr("Successfully loaded \"%1\" item image [%2].");

	for(int blockID = 1; blockID < MAX_BLOCKID; blockID++)
	{
		QString itemImageFilename(qApp->applicationDirPath() + ITEMS_IMAGES_PATH + Blocks::byId(blockID).name() + ".png");
		QImage qim_itemImage(itemImageFilename);
		if(qim_itemImage.isNull()) {
			lwarning(Channel_Textures, errorString.arg(itemImageFilename, Blocks::byId(blockID).name()));
		}
		else {
			Blocks::byId(blockID).setItemImage(qim_itemImage);
			ldebug(Channel_Textures, loadedString.arg(Blocks::byId(blockID).name(), itemImageFilename));
		}
	}
}

int RessourceManager::nextPowerOf2(uint x)
{
	const int MAX_POWER = 30;
	static uint powersOfTwo[MAX_POWER];
	static bool initialized = false;

	if(!initialized) {
		powersOfTwo[0] = 1;
		for(int i = 1; i < MAX_POWER; ++i) {
			powersOfTwo[i] = 2 * powersOfTwo[i - 1];
		}
		initialized = true;
	}

	for(int i = 1; i < MAX_POWER; ++i) {
		if(x >= powersOfTwo[i - 1] && x < powersOfTwo[i]) return powersOfTwo[i];
	}

	return -1;
}
