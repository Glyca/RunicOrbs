#include <QCoreApplication>

#include "LoadingWidget.h"

LoadingWidget::LoadingWidget(QWidget *parent) : QLabel(parent)
{
	setWindowTitle("The Runic Orbs");
	setGeometry(0, 0, 100, 30);
	setText(tr("Connecting to the server and loading your world\nPlease wait..."));
	show();
	QCoreApplication::processEvents();
}

LoadingWidget::~LoadingWidget()
{
	close();
}
