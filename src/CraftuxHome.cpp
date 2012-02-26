#include <QtGui>
#include <QGLWidget>

#include "CraftuxHome.h"
#include "GameWindow.h"
#include "LocalServerConnector.h"
#include "ServerConnector.h"
#include "ui_CraftuxHome.h"

CraftuxHome::CraftuxHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CraftuxHome)
{
    ui->setupUi(this);
    connect(ui->TestButton, SIGNAL(clicked()), this, SLOT(localTestLaunch()));
}

CraftuxHome::~CraftuxHome()
{
    delete ui;
}

void CraftuxHome::localTestLaunch()
{
	ui->TestButton->setText(tr("Création de votre monde en cours..."));
	this->repaint();

	// Création et génération du monde
	ServerConnector* connector = new LocalServerConnector();
	GameWindow* gameWindow = new GameWindow(connector);
	this->close();
	gameWindow->show();
}

