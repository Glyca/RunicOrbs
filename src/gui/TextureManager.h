#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QString>
#include <QtOpenGL>

// Classe qui gère toutes les textures OpenGL
// Classe singleton
class CTextureManager
{
public:
    CTextureManager();
    ~CTextureManager();

    static class CTextureManager* c_TextureManager;
    static CTextureManager* getTextureManager();

    void free(); // Libère toutes les ressources allouées par le gestionnaire de texture et le détruit

    GLuint loadTexture(const char* filename);

};

#define TextureManager (CTextureManager::getTextureManager())

#endif // TEXTUREMANAGER_H
