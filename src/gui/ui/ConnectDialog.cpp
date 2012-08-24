#include "server/ClientServer.h"
#include "ConnectDialog.h"
#include "ui_ConnectDialog.h"
#include "gui/GameWindow.h"
#include "LoadingWidget.h"
#include "ServerConnector.h"

ConnectDialog::ConnectDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ConnectDialog)
{
	ui->setupUi(this);
	connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onClick(QAbstractButton*)));
}

ConnectDialog::~ConnectDialog()
{
	delete ui;
}

void ConnectDialog::onClick(QAbstractButton* button)
{
	if(ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok) {
		LoadingWidget loadingWidget;
		ClientServer* clientServer = new ClientServer(ui->adressLineEdit->text(), ui->portSpinBox->value());

		if(clientServer->connect()) {
			m_connectorToBeUsed = new ServerConnector(clientServer);
			connect(m_connectorToBeUsed, SIGNAL(connected()), this, SLOT(startGame()));
			m_connectorToBeUsed->connect();
		}
		else {
			delete clientServer;
		}
	}
}

void ConnectDialog::startGame()
{
	GameWindow* window = new GameWindow(m_connectorToBeUsed);
	window->show();
	close();
}
