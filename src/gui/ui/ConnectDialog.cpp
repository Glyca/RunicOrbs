#include <QtXml/QtXml>

#include "server/ClientServer.h"
#include "ConnectDialog.h"
#include "ui_ConnectDialog.h"
#include "gui/GameWindow.h"
#include "LoadingWidget.h"
#include "ServerConnector.h"

const int MAX_SERVERS_IN_LIST = 8;
const char* SERVERS_FILENAME = "/last_servers.xml";

ConnectDialog::ConnectDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ConnectDialog)
{
	ui->setupUi(this);
	connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(selectServer(QListWidgetItem*)));
	connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onClick(QAbstractButton*)));
	loadServers();
}

ConnectDialog::~ConnectDialog()
{
	delete ui;
}

void ConnectDialog::onClick(QAbstractButton* button)
{
	if(ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok) {
		LoadingWidget loadingWidget;
		ClientServer* clientServer = new ClientServer(ui->adressLineEdit->text(), ui->portSpinBox->value(), ui->nameLineEdit->text());

		if(clientServer->connect()) {
			m_connectorToBeUsed = new ServerConnector(clientServer);
			connect(m_connectorToBeUsed, SIGNAL(connected()), this, SLOT(startGame()));
			m_connectorToBeUsed->connect();
			saveServers();
		}
		else {
			delete clientServer;
		}
	}
}

void ConnectDialog::selectServer(QListWidgetItem* item)
{
	QStringList splittedServer = item->text().split(":");
	ui->adressLineEdit->setText(splittedServer[0]);
	ui->portSpinBox->setValue(QVariant(splittedServer[1]).toInt());
}

void ConnectDialog::startGame()
{
	GameWindow* window = new GameWindow(m_connectorToBeUsed);
	window->show();
	close();
}

void ConnectDialog::loadServers()
{
	QDomDocument doc("xml");
	QFile file(qApp->applicationDirPath() + SERVERS_FILENAME);

	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}
	if (!doc.setContent(&file)) {
		file.close();
		return;
	}

	file.close();

	QDomElement rootNode = doc.documentElement(); // Access to the first child
	while(!rootNode.isNull())
	{
		if(rootNode.tagName() == "runicorbs")
		{
			QDomElement childNode = rootNode.firstChildElement();
			while(!childNode.isNull())
			{
				if(childNode.tagName() == "servers")
				{
					int nbOfParsedServers = 0;
					QDomElement serverNode = childNode.firstChildElement();
					while(!serverNode.isNull() && nbOfParsedServers < MAX_SERVERS_IN_LIST)
					{
						if(serverNode.tagName() == "server") // Parse a server
						{
							ui->listWidget->addItem(serverNode.text());
							nbOfParsedServers++;
						}
						serverNode = serverNode.nextSiblingElement();
					}
				}
				if(childNode.tagName() == "name")
				{
					ui->nameLineEdit->setText(childNode.text());
				}
				childNode = childNode.nextSiblingElement();
			}
		}
		rootNode = rootNode.nextSiblingElement();
	}
}

void ConnectDialog::saveServers()
{
	QDomDocument doc("xml");

	doc.appendChild(doc.createComment(QObject::tr("This file contains the last servers you played")));
	doc.appendChild(doc.createTextNode("\n")); // for nicer output

	QDomElement rootNode = doc.createElement("runicorbs");
	doc.appendChild(rootNode);

	QDomElement serversNode = doc.createElement("servers");
	rootNode.appendChild(serversNode);

	QDomElement firstServerNode = doc.createElement("server");
	firstServerNode.appendChild( doc.createTextNode(ui->adressLineEdit->text() + ":" + QString::number(ui->portSpinBox->value())) );
	serversNode.appendChild(firstServerNode);

	int nbOfSavedServers = 0;

	while(nbOfSavedServers < (MAX_SERVERS_IN_LIST - 1))
	{
		QListWidgetItem* item = ui->listWidget->takeItem(0);
		if(item != 0)
		{
			QDomElement serverNode = doc.createElement("server");
			serverNode.appendChild( doc.createTextNode(item->text()) );
			serversNode.appendChild(serverNode);
			nbOfSavedServers++;
		}
		else
		{
			break;
		}
	}

	QDomElement nameElement = doc.createElement("name");
	nameElement.appendChild( doc.createTextNode(ui->nameLineEdit->text()) );
	rootNode.appendChild(nameElement);

	QFile file(qApp->applicationDirPath() + SERVERS_FILENAME);

	if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate))
	{
		return;
	}

	file.write(doc.toByteArray());
	file.close();
}
