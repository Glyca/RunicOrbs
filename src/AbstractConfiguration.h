#ifndef ABSTRACTCONFIGURATION_H
#define ABSTRACTCONFIGURATION_H

#include <QString>

/*! An abstract class for configuations.
	One aim of the class is to provide a instant access to its values, that's why they are "hardcoded", and not in a map for example.
\note Configuration is not load from the disk until a load function is called */
class AbstractConfiguration
{
public:
	/*! Create a default configuration */
	AbstractConfiguration();
	/*! Load the configuration from a file */
	AbstractConfiguration(const QString& filename);

	/*! Load the configuration from the configuration file */
	virtual void loadDefaultConfigFile() = 0;

	/*! Populate config with default values */
	virtual void defaultValues() = 0;

	void setFilename(const QString& filename);
	virtual void setDefaultFilename() = 0;

	/*! Load the configuration from the disk */
	virtual void load() = 0;
	/*! Save the configuration on the disk */
	virtual void save() const = 0;

protected:
	QString s_filename;
};

#endif // ABSTRACTCONFIGURATION_H
