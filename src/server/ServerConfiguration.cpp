#include "ServerConfiguration.h"

#include <QtXml/QtXml>


ServerConfiguration::ServerConfiguration() : AbstractConfiguration()
{
	defaultValues(); // Set the defaults
}

ServerConfiguration::ServerConfiguration(const QString& filename) : AbstractConfiguration(filename)
{
	defaultValues(); // Set the defaults
}

void ServerConfiguration::loadDefaultConfigFile()
{
	setDefaultFilename();
	load();
}

void ServerConfiguration::defaultValues()
{
	// Here are the defaults value for the configuration :
	i_port = 51130;
	i_seed = 123456789;
}

void ServerConfiguration::setDefaultFilename()
{
	setFilename(qApp->applicationDirPath() + "/server.xml");
}

void ServerConfiguration::load()
{
	QDomDocument doc("xml");
	QFile file(s_filename);

	if (!file.open(QIODevice::ReadOnly))
	{
		qWarning() << QObject::tr("No server configuration file founded. Creating a new one!");
		save();
		return;
	}
	if (!doc.setContent(&file)) {
		qCritical() << QObject::tr("Can't parse server configuration file %1").arg(s_filename);
		file.close();
		return;
	}

	file.close();

	QDomElement rootNode = doc.documentElement(); // Access to the first child
	while(!rootNode.isNull())
	{
		if(rootNode.tagName() == "craftux")
		{
			QDomElement craftuxNode = rootNode.firstChildElement();
			while(!craftuxNode.isNull())
			{
				if(craftuxNode.tagName() == "network")
				{
					QDomElement networkNode = craftuxNode.firstChildElement();
					while(!networkNode.isNull())
					{
						if(networkNode.tagName() == "port") // Parse server port
						{
							setPort(networkNode.text().toUShort());
						}
						networkNode = networkNode.nextSiblingElement();
					}
				}
				craftuxNode = craftuxNode.nextSiblingElement();
			}
		}
		rootNode = rootNode.nextSiblingElement();
	}
}

void ServerConfiguration::save() const
{
	QDomDocument doc("xml");

	doc.appendChild(doc.createComment(QObject::tr("This is the Craftux configuration file")));
	doc.appendChild(doc.createTextNode("\n")); // for nicer output

	QDomElement rootNode = doc.createElement("craftux");
	doc.appendChild(rootNode);

	QDomElement networkNode = doc.createElement("network");
	networkNode.appendChild(doc.createComment(QObject::tr("Settings for server's network")));

	QDomElement portNode = doc.createElement("port");
	portNode.appendChild( doc.createTextNode(QVariant(getPort()).toString()) );
	networkNode.appendChild(portNode);

	rootNode.appendChild(networkNode);

	QFile file(s_filename);

	if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate))
	{
		qCritical() << QObject::tr("Error opening server configuration file %1").arg(s_filename);
		return;
	}

	file.write(doc.toByteArray());
	file.close();
}

quint16 ServerConfiguration::getPort() const
{
	return i_port;
}

void ServerConfiguration::setPort(quint16 port)
{
	i_port = port;
}

int ServerConfiguration::getSeed() const
{
	return i_seed;
}

void ServerConfiguration::setSeed(int seed)
{
	i_seed = seed;
}
