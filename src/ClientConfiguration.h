#ifndef CLIENTCONFIGURATION_H
#define CLIENTCONFIGURATION_H

#include <QString>

/*! Manage the configuration of the Craftux client */
class ClientConfiguration
{
public:
    enum Action{
        UP,
        DOWN,
        LEFT,
        RIGHT,
        JUMP,
        NBVAL
    };

    /*! Create a default configuration */
    ClientConfiguration();
    /*! Load the configuration from a file */
    ClientConfiguration(const QString& filename);

    //~ClientConfiguration();

    /*! Create tab */
    void initKeyMap();

    /*! Load the configuration from the configuration file */
    void loadDefaultConfigFile();

    /*! Populate config with default values */
    void defaultValues();
    void reloadDefault();

    void setFilename(const QString& filename);
    void setDefaultFilename();

    /*! Load the configuration from the disk */
    void load();
    /*! Save the configuration on the disk */
    void save() const;

    /* Accessors have willingly a get or set prefix to enphasize that it's a provider class */

    int getFps() const;
    void setFps(const int fps);

    int getSeed() const;
    void setSeed(const int seed);

    QString getKeyVal(const Action action) const;
    int getKey(const Action action) const;
    void setKey(const Action action, const int value);
    int getViewDistance() const;
    void setViewDistance(const int distance);

    bool getSmoothShades() const;
    void setSmoothShades(const bool smooth);

    int getTextureFiltering() const;
    void setTextureFiltering(const int filtering);

private:
    QString s_filename;
    int i_fps;
    int i_seed;
    int *i_keyMap;
    int i_viewDistance;
    bool b_smoothShades;
    int i_textureFiltering;
};

#endif // CLIENTCONFIGURATION_H
