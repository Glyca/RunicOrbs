#include <QtGui>
#include <QGLWidget>

#include "BlockInfo.h"
#include "CraftuxHome.h"
#include "GameWindow.h"
#include "LocalServerConnector.h"
#include "MainWindow.h"
#include "ServerConnector.h"
#include "ui_CraftuxHome.h"

MainWindow* mw;

CraftuxHome::CraftuxHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CraftuxHome)
{
    ui->setupUi(this);

    ui->dial->setRange(1, MAX_WORLD_X);
    ui->dial_2->setRange(1, MAX_WORLD_Y);
    ui->dial_3->setRange(1, MAX_WORLD_Z);

    ui->dial->setValue(DEFAULT_WORLD_X);
    valueChangedX(DEFAULT_WORLD_X);
    ui->dial_2->setValue(DEFAULT_WORLD_Y);
    valueChangedY(DEFAULT_WORLD_Y);
    ui->dial_3->setValue(DEFAULT_WORLD_Z);
    valueChangedZ(DEFAULT_WORLD_Z);
    ui->dial_5->setValue(DEFAULT_WORLD_SEA);
    valueChangedSEA(DEFAULT_WORLD_SEA);

    calcBlockNumber();

    connect(ui->TestButton, SIGNAL(clicked()), this, SLOT(localTestLaunch()));
	connect(ui->test2Button, SIGNAL(clicked()), this, SLOT(localTestLaunch2()));

    connect(ui->dial, SIGNAL(valueChanged(int)), this, SLOT(valueChangedX(int)));
    connect(ui->dial_2, SIGNAL(valueChanged(int)), this, SLOT(valueChangedY(int)));
    connect(ui->dial_3, SIGNAL(valueChanged(int)), this, SLOT(valueChangedZ(int)));
    connect(ui->dial_5, SIGNAL(valueChanged(int)), this, SLOT(valueChangedSEA(int)));
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
	WorldBlocks* worldBlocks = new WorldBlocks(ui->dial->value(), ui->dial_2->value(), ui->dial_3->value(), ui->dial_5->value());
	worldBlocks->generate(0);

	mw = new MainWindow(worldBlocks);
	this->close();
	mw->show();
}

void CraftuxHome::localTestLaunch2()
{
	ui->TestButton->setText(tr("Création de votre monde en cours..."));
	this->repaint();

	// Création et génération du monde
	ServerConnector* connector = new LocalServerConnector();
	GameWindow* gameWindow = new GameWindow(connector);
	this->close();
	gameWindow->show();
}

void CraftuxHome::valueChangedX(int value)
{
    ui->label_2->setText(((QVariant)value).toString());
    calcBlockNumber();
}

void CraftuxHome::valueChangedY(int value)
{
    ui->label_4->setText(((QVariant)value).toString());
    ui->dial_5->setRange(1, value);
    calcBlockNumber();
}

void CraftuxHome::valueChangedZ(int value)
{
    ui->label_6->setText(((QVariant)value).toString());
    calcBlockNumber();
}

void CraftuxHome::valueChangedSEA(int value)
{
    ui->label_10->setText(((QVariant)value).toString());
    calcBlockNumber();
}

void CraftuxHome::calcBlockNumber()
{
    int number =  ui->dial->value() * ui->dial_2->value() * ui->dial_3->value();
    QString number_string = QLocale().toString((float)number, 'f', 0);

    ui->label_11->setText(tr("Nombre total de blocs à générer : ") + number_string);
}

