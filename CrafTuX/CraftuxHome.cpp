#include <QtGui>
#include <QGLWidget>

#include "CraftuxHome.h"
#include "ui_CraftuxHome.h"
#include "MainWindow.h"
#include "BlockInfo.h"

MainWindow* mw;

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
   /* WrapperWindow* ww = new WrapperWindow();
    ww->show();*/

    mw = new MainWindow();
    mw->show();

    close();

    /*QGLWidget* qw = new QGLWidget();
    qw->show();*/

}
