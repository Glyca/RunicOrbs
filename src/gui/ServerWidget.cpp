#include "server/MultiplayerServerThread.h"
#include "ServerWidget.h"
#include "ui_ServerWidget.h"

ServerWidget::ServerWidget(QWidget *parent) : QTabWidget(parent), ui(new Ui::ServerWidget)
{
	ui->setupUi(this);
	serverStopped();

	connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startServer()));
	connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopServer()));
}

ServerWidget::~ServerWidget()
{
	delete ui;
}

void ServerWidget::startServer()
{
	ui->serverSatuslabel->setText(tr("The server starts"));
	ui->startButton->setEnabled(false);
	m_server = new MultiplayerServerThread();
	serverStarted();
}

void ServerWidget::stopServer()
{
	ui->serverSatuslabel->setText(tr("The server is being stopped"));
	ui->stopButton->setEnabled(false);
	delete m_server;
	serverStopped();
}

void ServerWidget::serverStarted()
{
	ui->serverSatuslabel->setText(tr("The server is running"));
	ui->stopButton->setEnabled(true);
	ui->startButton->setEnabled(false);
}

void ServerWidget::serverStopped()
{
	ui->serverSatuslabel->setText(tr("The server is not running"));
	ui->stopButton->setEnabled(false);
	ui->startButton->setEnabled(true);
}
