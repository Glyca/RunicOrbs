#include <QCloseEvent>
#include <QDesktopWidget>
#include "Log.h"
#include "server/ServerConfiguration.h"
#include "server/MultiplayerServer.h"
#include "ServerWidget.h"
#include "ui_ServerWidget.h"

// Id of tabs
const int OVERVIEW_TABID = 0;
const int CONSOLE_TABID = 1;

ServerWidget::ServerWidget(QWidget *parent) : QTabWidget(parent), ui(new Ui::ServerWidget)
{
	ui->setupUi(this);
	serverStopped();

	connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startServer()));
	connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopServer()));
	connect(ui->consoleClearButton, SIGNAL(clicked()), this, SLOT(clearConsole()));
	connect(&Log::instance(), SIGNAL(print(const QString&)), this, SLOT(printLine(const QString&)));

	// Center the window on the screen
	QDesktopWidget* desktop = QApplication::desktop();
	move( (desktop->width() - width()) / 2 , (desktop->height() - height()) / 2 - 50 );
}

ServerWidget::~ServerWidget()
{
	delete ui;
}

void ServerWidget::closeEvent(QCloseEvent* closeEvent)
{
	closeEvent->accept();
	deleteLater();
}

void ServerWidget::startServer()
{
	ui->serverSatuslabel->setText(tr("The server starts"));
	ui->startButton->setEnabled(false);
	// Go to the console tab
	setCurrentIndex(CONSOLE_TABID);
	// Load server configuration and start it
	ServerConfiguration* serverConfiguration = new ServerConfiguration();
	serverConfiguration->loadDefaultConfigFile();
	m_server = new MultiplayerServer(serverConfiguration);
	serverStarted();
}

void ServerWidget::stopServer()
{
	ui->serverSatuslabel->setText(tr("The server is being stopped"));
	ui->stopButton->setEnabled(false);
	delete m_server;
	serverStopped();
}

void ServerWidget::printLine(const QString& line)
{
	ui->consoleTextBrowser->append(line);
}

void ServerWidget::clearConsole()
{
	ui->consoleTextBrowser->clear();
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
	// Go to the overview tab
	setCurrentIndex(OVERVIEW_TABID);
}
