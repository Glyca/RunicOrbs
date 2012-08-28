#include <QCoreApplication>

#include "server/ClientServer.h"
#include "gui/GameWindow.h"
#include "LoadingWidget.h"
#include "server/LocalServer.h"
#include "ServerConnector.h"

LoadingWidget::LoadingWidget() : QLabel()
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

bool LoadingWidget::loadSoloGame()
{
	LocalServer* localServer = new LocalServer(qApp, 123);
	m_connectorToBeUsed = new ServerConnector(localServer);
	connect(m_connectorToBeUsed, SIGNAL(connected()), this, SLOT(startGame()));
	localServer->start();
	return true;
}

bool LoadingWidget::loadMultiplayerGame(const QString& hostName, quint16 port, const QString& nickName)
{
	ClientServer* clientServer = new ClientServer(hostName, port, nickName);

	m_connectorToBeUsed = new ServerConnector(clientServer);
	connect(m_connectorToBeUsed, SIGNAL(connected()), this, SLOT(startGame()));

	if(clientServer->connect()) {
		clientServer->start();
		return true;
	}
	else {
		delete clientServer;
		return false;
	}
}

void LoadingWidget::startGame()
{
	GameWindow* window = new GameWindow(m_connectorToBeUsed);
	window->show();
	close();
}
