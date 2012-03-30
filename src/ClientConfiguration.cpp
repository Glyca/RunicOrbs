#include "ClientConfiguration.h"

#include <QtXml/QtXml>

ClientConfiguration::ClientConfiguration()
{
    initKeyMap();
    //defaultValues();
    //reloadDefault();
    setDefaultFilename();
    loadDefaultConfigFile();
}

ClientConfiguration::ClientConfiguration(const QString& filename) : s_filename(filename)
{
	defaultValues(); // Set the defaults
}

void ClientConfiguration::initKeyMap()
{
    i_keyMap=new int[NBVAL];
    for(int i=0;i<=NBVAL;i++)
        i_keyMap[i]=32;
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
    /*
    <up>90</up>
   <left>81</left>
   <down>83</down>
   <right>68</right>
   <jump>32</jump>
   */
    /*i_keyMap[UP] = 'z'-32;
    i_keyMap[LEFT] = 'q'-32;
    i_keyMap[DOWN] = 's'-32;
    i_keyMap[RIGHT] = 'd'-32;
    i_keyMap[JUMP] = 32;*/
}

void ClientConfiguration::reloadDefault()
{
    // Here are the defaults value for the configuration :
    i_fps = 60;
    i_seed = 123456789;
    i_keyMap[UP] = 'z'-32;
    i_keyMap[LEFT] = 'q'-32;
    i_keyMap[DOWN] = 's'-32;
    i_keyMap[RIGHT] = 'd'-32;
    i_keyMap[JUMP] = 32;
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
							i_seed = gameChildNode.text().toInt();
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
							i_fps = graphicsChildNode.text().toInt();
						}
						graphicsChildNode = graphicsChildNode.nextSiblingElement();
					}
				}
                else if(craftuxChildNode.tagName() == "keymap")
                {
                    QDomElement keyChildNode = craftuxChildNode.firstChildElement();
                    while(!keyChildNode.isNull())
                    {
                        if(keyChildNode.tagName() == "move") // Parse movment key
                        {
                            QDomElement moveChildNode = keyChildNode.firstChildElement();
                            while(!moveChildNode.isNull())
                            {
                                if(moveChildNode.tagName() == "up")
                                {
                                    i_keyMap[UP]=moveChildNode.text().toInt();
                                }
                                else if(moveChildNode.tagName() == "left")
                                {
                                    i_keyMap[LEFT]=moveChildNode.text().toInt();
                                }
                                else if(moveChildNode.tagName() == "down")
                                {
                                    i_keyMap[DOWN]=moveChildNode.text().toInt();
                                }
                                else if(moveChildNode.tagName() == "right")
                                {
                                    i_keyMap[RIGHT]=moveChildNode.text().toInt();
                                }
                                moveChildNode = moveChildNode.nextSiblingElement();
                            }
                        }
                        keyChildNode = keyChildNode.nextSiblingElement();
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

    /*! Game Element*/
	QDomElement gameNode = doc.createElement("game");
	gameNode.appendChild(doc.createComment(QObject::tr("Settings for gameplay")));

	QDomElement seedNode = doc.createElement("seed");
	seedNode.appendChild( doc.createTextNode(QVariant(i_seed).toString()) );
	gameNode.appendChild(seedNode);

	rootNode.appendChild(gameNode);

    /*! Graphic Element*/
	QDomElement graphicsNode = doc.createElement("graphics");
	graphicsNode.appendChild(doc.createComment(QObject::tr("Configure graphics")));

	QDomElement fpsNode = doc.createElement("fps");
	fpsNode.appendChild( doc.createTextNode(QVariant(i_fps).toString()) );
	graphicsNode.appendChild(fpsNode);

    rootNode.appendChild(graphicsNode);

    /*! Key Element*/
    QDomElement keyNode = doc.createElement("keymap");
    keyNode.appendChild(doc.createComment(QObject::tr("Configure keymap")));

    QDomElement moveNode = doc.createElement("move");
    moveNode.appendChild(doc.createComment(QObject::tr("Configure movement key")));

    QDomElement upNode = doc.createElement("up");
    upNode.appendChild( doc.createTextNode(QVariant(i_keyMap[UP]).toString()) );
    moveNode.appendChild(upNode);
    QDomElement leftNode = doc.createElement("left");
    leftNode.appendChild( doc.createTextNode(QVariant(i_keyMap[LEFT]).toString()) );
    moveNode.appendChild(leftNode);
    QDomElement downNode = doc.createElement("down");
    downNode.appendChild( doc.createTextNode(QVariant(i_keyMap[DOWN]).toString()) );
    moveNode.appendChild(downNode);
    QDomElement rightNode = doc.createElement("right");
    rightNode.appendChild( doc.createTextNode(QVariant(i_keyMap[RIGHT]).toString()) );
    moveNode.appendChild(rightNode);
    QDomElement jumpNode = doc.createElement("jump");
    jumpNode.appendChild( doc.createTextNode(QVariant(i_keyMap[JUMP]).toString()) );
    moveNode.appendChild(jumpNode);

    keyNode.appendChild(moveNode);

    rootNode.appendChild(keyNode);

	QByteArray content = doc.toByteArray();
	QFile file(s_filename);

	if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate))
	{
		qCritical() << QObject::tr("Error opening client configuration file %1").arg(s_filename);
		return;
	}

	file.write(content);
	file.close();
}


/*! Get and Set method*/
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

QString ClientConfiguration::getKeyVal(const Action action) const
{
    QString tmp="";
    char preTmp;
    int val=getKey(action);
    if(val>=Qt::Key_A && val<=Qt::Key_Z)
    {
        preTmp=val;
        tmp=preTmp;
        return tmp;
    }
    else if(val==Qt::Key_Space)
        return "Space";
    else if(val>=Qt::Key_F1 && val<=Qt::Key_F35)
    {
        QString qStr = QString::number(val-16777263);
        return "F"+qStr;
    }
    else if(val==Qt::Key_Control)
        return "Control";
    else if(val==Qt::Key_Shift)
        return "Shift";
    else if(val==Qt::Key_Alt)
        return "Alt";
    else
        return "Problem in value";

}

int ClientConfiguration::getKey(const Action action) const
{
    return i_keyMap[action];
}

void ClientConfiguration::setKey(const Action action, const int value)
{
    i_keyMap[action]=value;
}
