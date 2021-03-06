#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QString>
#include <QTabWidget>

class MultiplayerServer;

namespace Ui {
	class ServerWidget;
}

class ServerWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit ServerWidget(QWidget *parent = 0);
	~ServerWidget();

	void closeEvent(QCloseEvent* closeEvent);

public slots:
	void startServer();
	void stopServer();
	void printLine(const QString &line);
	void clearConsole();

private:
	void serverStarted();
	void serverStopped();

	Ui::ServerWidget *ui;
	MultiplayerServer* m_server;
};

#endif // SERVERWIDGET_H
