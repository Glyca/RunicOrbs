#include "ConnectDialog.h"
#include "ui_ConnectDialog.h"
#include "GameWindow.h"
#include "RemoteServerConnector.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ConnectDialog)
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
		RemoteServerConnector* connector = new RemoteServerConnector();
		GameWindow* window = new GameWindow(connector);
		window->show();
	}
}
