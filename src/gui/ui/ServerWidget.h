#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QTabWidget>

class MultiplayerServerThread;

namespace Ui {
	class ServerWidget;
}

class ServerWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit ServerWidget(QWidget *parent = 0);
	~ServerWidget();

public slots:
	void startServer();
	void stopServer();

private:
	void serverStarted();
	void serverStopped();

	Ui::ServerWidget *ui;
	MultiplayerServerThread* m_server;
};

#endif // SERVERWIDGET_H
