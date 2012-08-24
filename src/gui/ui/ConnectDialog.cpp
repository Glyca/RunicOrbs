#include "server/ClientServer.h"
#include "ConnectDialog.h"
#include "ui_ConnectDialog.h"
#include "gui/GameWindow.h"
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
		QLabel* info = new QLabel(tr("Connecting to the server\nPlease wait..."), 0, Qt::Popup);
		info->show();
		QCoreApplication::processEvents();
		m_connectorToBeUsed = new ServerConnector(new ClientServer(ui->adressLineEdit->text(), ui->portSpinBox->value()));
		connect(m_connectorToBeUsed, SIGNAL(connected()), this, SLOT(startGame()));
		m_connectorToBeUsed->connect();
	}
}

void ConnectDialog::startGame()
{
	GameWindow* window = new GameWindow(m_connectorToBeUsed);
	window->show();
	close();
}
