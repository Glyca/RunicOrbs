#include <QtXml/QtXml>

#include "server/ClientServer.h"
#include "ConnectDialog.h"
#include "ui_ConnectDialog.h"
#include "LoadingWidget.h"

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
		LoadingWidget* loadingWidget = new LoadingWidget();
		if(loadingWidget->loadMultiplayerGame(ui->adressLineEdit->text(), ui->portSpinBox->value(), ui->nameLineEdit->text()))
		{
			saveServers();
		}
	}
}

void ConnectDialog::selectServer(QListWidgetItem* item)
{
	QStringList splittedServer = item->text().split(":");
	ui->adressLineEdit->setText(splittedServer[0]);
	ui->portSpinBox->setValue(QVariant(splittedServer[1]).toInt());
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
					ui->adressLineEdit->setFocus(); // Since we have the name, focus on the adressLineEdit
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
	QString newServerLine = ui->adressLineEdit->text() + ":" + QString::number(ui->portSpinBox->value());
			firstServerNode.appendChild( doc.createTextNode(newServerLine) );
	serversNode.appendChild(firstServerNode);

	int nbOfSavedServers = 0;

	while(nbOfSavedServers < (MAX_SERVERS_IN_LIST - 1))
	{
		QListWidgetItem* item = ui->listWidget->takeItem(0);
		if(item != 0)
		{
			if(item->text() != newServerLine) // If it isn't the new server, save it
			{
				QDomElement serverNode = doc.createElement("server");
				serverNode.appendChild( doc.createTextNode(item->text()) );
				serversNode.appendChild(serverNode);
			}
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
