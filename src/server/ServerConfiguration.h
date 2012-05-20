#ifndef SERVERCONFIGURATION_H
#define SERVERCONFIGURATION_H

#include "AbstractConfiguration.h"

/*! Manages the configuration of The Runic Orbs server */
class ServerConfiguration : public AbstractConfiguration
{
public:
	ServerConfiguration();
	ServerConfiguration(const QString& filename);

	virtual void defaultValues();
	virtual void setDefaultFilename();
	virtual void loadDefaultConfigFile();

	virtual void load();
	virtual void save() const;

	quint16 getPort() const;
	void setPort(quint16 port);

private:
	quint16 i_port;
};

#endif // SERVERCONFIGURATION_H
