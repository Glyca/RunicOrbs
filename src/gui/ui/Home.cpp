#include <QtGui>
#include <QGLWidget>

#include "Home.h"
#include "ConnectDialog.h"
#include "gui/GameWindow.h"
#include "LoadingWidget.h"
#include "server/LocalServer.h"
#include "OptionsDialog.h"
#include "ServerConnector.h"
#include "ServerWidget.h"
#include "version.h"
#include "ui_Home.h"

Home::Home(QWidget *parent) :
	QWidget(parent), ui(new Ui::Home), b_optionDialogOpened(false), m_optionsDialog(NULL), b_serverWidgetOpened(false), m_serverWidget(NULL)
{
	ui->setupUi(this);
	QString imageName(qApp->applicationDirPath() + "/gfx/logo.png");
	if(QFile(imageName).exists()) {
		ui->titleLabel->setPixmap(QPixmap(imageName));
	}
	else {
		ui->titleLabel->setText("The Runic Orbs");
	}

	connect(ui->soloButton, SIGNAL(clicked()), this, SLOT(soloGameLaunch()));
	connect(ui->multiButton, SIGNAL(clicked()), this, SLOT(openConnectDialog()));
	connect(ui->serverButton, SIGNAL(clicked()), this, SLOT(openServerWidget()));
	connect(ui->optionsButton, SIGNAL(clicked()), this, SLOT(openOptions()));
	connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
	ui->versionLabel->setText(tr("version %1").arg(TRO_VERSION));
	// Center the window on the screen
	QDesktopWidget* desktop = QApplication::desktop();
	move( (desktop->width() - width()) / 2 , (desktop->height() - height()) / 2 - 50 );
}

Home::~Home()
{
	delete ui;
}

void Home::soloGameLaunch()
{
	// Création et génération du monde
	LoadingWidget loadingWidget;
	LocalServer* localServer = new LocalServer(qApp, 123);
	ServerConnector* connector = new ServerConnector(localServer);
	GameWindow* gameWindow = new GameWindow(connector);
	gameWindow->show();
	close();
}

void Home::openOptions()
{
	if(b_optionDialogOpened)
	{
		// we don't open two options dialog at one time
	}
	else
	{
		if(m_optionsDialog != NULL) delete m_optionsDialog;
		m_optionsDialog = new OptionsDialog(this);
		m_optionsDialog->show();
		connect(m_optionsDialog, SIGNAL(finished(int)), this, SLOT(optionsClosed()));
		b_optionDialogOpened = true;
	}
}

void Home::optionsClosed()
{
	b_optionDialogOpened = false;
	m_optionsDialog = NULL;
}

void Home::openConnectDialog()
{
	ConnectDialog* connectDialog = new ConnectDialog();
	this->close();
	connectDialog->show();
}

void Home::openServerWidget()
{
	if(b_serverWidgetOpened)
	{
		// we don't open two server widgets at one time
	}
	else
	{
		if(m_serverWidget != NULL) delete m_serverWidget;
		m_serverWidget = new ServerWidget();
		m_serverWidget->show();
		connect(m_serverWidget, SIGNAL(destroyed()), this, SLOT(serverWidgetClosed()));
		b_serverWidgetOpened = true;
	}
}

void Home::serverWidgetClosed()
{
	b_serverWidgetOpened = false;
	m_serverWidget = NULL;
}
