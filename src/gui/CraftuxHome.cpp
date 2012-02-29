﻿#include <QtGui>
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
	connect(ui->soloButton, SIGNAL(clicked()), this, SLOT(soloGameLaunch()));
	connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
}

CraftuxHome::~CraftuxHome()
{
    delete ui;
}

void CraftuxHome::soloGameLaunch()
{
	// Création et génération du monde
	ServerConnector* connector = new LocalServerConnector();
	GameWindow* gameWindow = new GameWindow(connector);
	this->close();
	gameWindow->show();
}
