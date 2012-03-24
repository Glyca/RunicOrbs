#ifndef CLIENTCONFIGURATION_H
#define CLIENTCONFIGURATION_H

#include <QString>

class ClientConfiguration
{
public:
	/*! Create a default configuration */
	ClientConfiguration();
	/*! Load the configuration from a file */
	ClientConfiguration(const QString& filename);

	/*! Load the configuration from the configuration file */
	void loadDefaultConfigFile();

	/*! Populate config with default values */
	void defaultValues();

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

	int getViewDistance() const;
	void setViewDistance(const int distance);

	bool getSmoothShades() const;
	void setSmoothShades(const bool smooth);

private:
	QString s_filename;
	int i_fps;
	int i_seed;
	int i_viewDistance;
	bool b_smoothShades;
};

#endif // CLIENTCONFIGURATION_H
