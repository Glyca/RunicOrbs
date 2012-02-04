#include "TextureManager.h"
#include "CraftuxHome.h"
#include <QtGlobal>
#include <QDir>
#include <QDir>

CTextureManager *CTextureManager::c_TextureManager = 0;

CTextureManager::CTextureManager()
{
    qDebug("Gestionaire de textures construit");
}

CTextureManager::~CTextureManager()
{

}

CTextureManager* CTextureManager::getTextureManager()
{
    if(c_TextureManager == 0)
    {
	c_TextureManager = new CTextureManager;
    }
    return c_TextureManager;
}

void CTextureManager::free()
{
    delete c_TextureManager;
}

GLuint CTextureManager::loadTexture(const char* filename)
{
  /*  // ouverture de l'image
    QString currentDir =  QDir::currentPath();
    qDebug() << "Dossier actuel : " << currentDir;
    QString currentPath(currentDir);
    currentPath.append("/");
    currentPath.append(filename);
    qDebug() << "Chemin complet : " << currentPath;

    qDebug() << "Tentative d'ouverture du fichier...";
    QFile qfile_myfile(currentPath);
    if(qfile_myfile.isReadable()) qDebug() << "Le fichier est lisible";*/

    // ouverture de l'image
    QString qs_filename = QString(filename);
    QImage qim_TextureImage(qs_filename);
    GLuint gi_textureID[1];
    if(qim_TextureImage.isNull()) qDebug("Texture [%s] load failed !", filename);
    QImage qim_Texture = mw->convertToGLFormat(qim_TextureImage);
    // Demandons un ID de texture libre
    glGenTextures(1, &gi_textureID[0]);
    // Bindons cet ID
    glBindTexture(GL_TEXTURE_2D, gi_textureID[0]);
    // Filtrage lorsqu'on rétrécit la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // Filtrage lorsqu'on étire la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // Infos : http://gregs-blog.com/2008/01/17/opengl-texture-filter-parameters-explained/

    // the texture wraps over at the edges (repeat)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Envoi de la texture
    //if(1)
    {
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, qim_Texture.width(), qim_Texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, qim_Texture.bits());
    }
    //else // Méthode sans les mimpas (moche !)
    {
	//glTexImage2D( GL_TEXTURE_2D, 0, 3, qim_Texture.width(), qim_Texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, qim_Texture.bits() );
    }
    return gi_textureID[0];
    //return mw->bindTexture(qim_Texture, GL_TEXTURE_2D, GL_RGBA);
}
