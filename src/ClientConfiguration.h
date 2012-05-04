#ifndef CLIENTCONFIGURATION_H
#define CLIENTCONFIGURATION_H

#include "AbstractConfiguration.h"

enum Action {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	JUMP,
	NBVAL
};

/*! Manage the configuration of The Runic Orbs client */
class ClientConfiguration : public AbstractConfiguration
{
public:
	ClientConfiguration();
	ClientConfiguration(const QString& filename);

	/*! Create tab */
	void initKeyMap();

	/*! Load the configuration from the configuration file */
	virtual void loadDefaultConfigFile();

	/*! Populate config with default values */
	virtual void defaultValues();

	virtual void setDefaultFilename();

	/*! Load the configuration from the disk */
	virtual void load();
	/*! Save the configuration on the disk */
	virtual void save() const;

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

	bool getAntialiasing() const;
	void setAntialiasing(const bool enabled);

	int getTextureFiltering() const;
	void setTextureFiltering(const int filtering);

private:
	int i_fps;
	int i_seed;
	int *i_keyMap;
	int i_viewDistance;
	bool b_smoothShades;
	bool b_antialiasing;
	int i_textureFiltering;
};

#endif // CLIENTCONFIGURATION_H
