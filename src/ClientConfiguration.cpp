#include "ClientConfiguration.h"

#include <QtXml/QtXml>

ClientConfiguration::ClientConfiguration()
{
	defaultValues();
	setDefaultFilename();
}

ClientConfiguration::ClientConfiguration(const QString& filename) : s_filename(filename)
{
	defaultValues(); // Set the defaults
}

void ClientConfiguration::loadDefaultConfigFile()
{
	setDefaultFilename();
	load();
}

void ClientConfiguration::defaultValues()
{
	// Here are the defaults value for the configuration :
	i_fps = 60;
	i_seed = 123456789;
	i_viewDistance = 2;
	b_smoothShades = true;
	i_textureFiltering = 2;
}

void ClientConfiguration::setFilename(const QString& filename)
{
	s_filename = filename;
}

void ClientConfiguration::setDefaultFilename()
{
	setFilename(qApp->applicationDirPath() + "/config.xml");
}

void ClientConfiguration::load()
{
	QDomDocument doc("xml");
	QFile file(s_filename);

	if (!file.open(QIODevice::ReadOnly))
	{
		qWarning() << QObject::tr("No configuration file founded. Creating a new one!");
		save();
		return;
	}
	if (!doc.setContent(&file)) {
		qCritical() << QObject::tr("Can't parse client configuration file %1").arg(s_filename);
		file.close();
		return;
	}

	file.close();

	QDomElement childNode = doc.documentElement(); // Access to the first child
	while(!childNode.isNull())
	{
		if(childNode.tagName() == "craftux")
		{
			QDomElement craftuxChildNode = childNode.firstChildElement();
			while(!craftuxChildNode.isNull())
			{
				if(craftuxChildNode.tagName() == "game")
				{
					QDomElement gameChildNode = craftuxChildNode.firstChildElement();
					while(!gameChildNode.isNull())
					{
						if(gameChildNode.tagName() == "seed") // Parse seed
						{
							setSeed(gameChildNode.text().toInt());
						}
						gameChildNode = gameChildNode.nextSiblingElement();
					}
				}
				else if(craftuxChildNode.tagName() == "graphics")
				{
					QDomElement graphicsChildNode = craftuxChildNode.firstChildElement();
					while(!graphicsChildNode.isNull())
					{
						if(graphicsChildNode.tagName() == "fps") // Parse FPS
						{
							setFps(graphicsChildNode.text().toInt());
						}
						if(graphicsChildNode.tagName() == "viewDistance") // Parse viewDistance
						{
							setViewDistance(graphicsChildNode.text().toInt());
						}
						if(graphicsChildNode.tagName() == "smoothShades") // Parse Shade model
						{
							setSmoothShades(QVariant(graphicsChildNode.text()).toBool());
						}
						if(graphicsChildNode.tagName() == "textureFiltering") // Parse textureFiltering
						{
							setTextureFiltering(graphicsChildNode.text().toInt());
						}
						graphicsChildNode = graphicsChildNode.nextSiblingElement();
					}
				}
				craftuxChildNode = craftuxChildNode.nextSiblingElement();
			}
		}
		childNode = childNode.nextSiblingElement();
	}
}

void ClientConfiguration::save() const
{
	QDomDocument doc("xml");

	doc.appendChild(doc.createComment(QObject::tr("This is the Craftux configuration file")));
	doc.appendChild(doc.createTextNode("\n")); // for nicer output

	QDomElement rootNode = doc.createElement("craftux");
	doc.appendChild(rootNode);

	QDomElement gameNode = doc.createElement("game");
	gameNode.appendChild(doc.createComment(QObject::tr("Settings for gameplay")));

	QDomElement seedNode = doc.createElement("seed");
	seedNode.appendChild( doc.createTextNode(QVariant(getSeed()).toString()) );
	gameNode.appendChild(seedNode);

	rootNode.appendChild(gameNode);
	QDomElement graphicsNode = doc.createElement("graphics");
	graphicsNode.appendChild(doc.createComment(QObject::tr("Configure graphics")));

	QDomElement fpsNode = doc.createElement("fps");
	fpsNode.appendChild( doc.createTextNode(QVariant(getFps()).toString()) );
	graphicsNode.appendChild(fpsNode);

	QDomElement viewDistanceNode = doc.createElement("viewDistance");
	viewDistanceNode.appendChild( doc.createTextNode(QVariant(getViewDistance()).toString()) );
	graphicsNode.appendChild(viewDistanceNode);

	QDomElement shadeModelNode = doc.createElement("smoothShades");
	shadeModelNode.appendChild( doc.createTextNode(QVariant(getSmoothShades()).toString()) );
	graphicsNode.appendChild(shadeModelNode);

	QDomElement textureFilteringNode = doc.createElement("textureFiltering");
	textureFilteringNode.appendChild( doc.createTextNode(QVariant(getTextureFiltering()).toString()) );
	graphicsNode.appendChild(textureFilteringNode);

	rootNode.appendChild(graphicsNode);

	QFile file(s_filename);

	if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate))
	{
		qCritical() << QObject::tr("Error opening client configuration file %1").arg(s_filename);
		return;
	}

	file.write(doc.toByteArray());
	file.close();
}

int ClientConfiguration::getFps() const
{
	return i_fps;
}

void ClientConfiguration::setFps(const int fps)
{
	i_fps = fps;
}

int ClientConfiguration::getSeed() const
{
	return i_seed;
}

void ClientConfiguration::setSeed(const int seed)
{
	i_seed = seed;
}

int ClientConfiguration::getViewDistance() const
{
	return i_viewDistance;
}

void ClientConfiguration::setViewDistance(const int distance)
{
	if(distance > 0) {
		i_viewDistance = distance;
	}
	else {
		i_viewDistance = 1;
	}
}

bool ClientConfiguration::getSmoothShades() const
{
	return b_smoothShades;
}

void ClientConfiguration::setSmoothShades(const bool smooth)
{
	b_smoothShades = smooth;
}

int ClientConfiguration::getTextureFiltering() const
{
	return i_textureFiltering;
}
void ClientConfiguration::setTextureFiltering(const int filtering)
{
	i_textureFiltering = filtering;
}

