#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

class QAbstractButton;
class ServerConnector;

namespace Ui {
	class ConnectDialog;
}

class ConnectDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ConnectDialog(QWidget *parent = 0);
	virtual ~ConnectDialog();

public slots:
	void onClick(QAbstractButton*);
	void selectServer(QListWidgetItem*);
	void startGame();

private:
	/*! Load last servers from the disk */
	void loadServers();
	void saveServers();

	Ui::ConnectDialog *ui;
	ServerConnector* m_connectorToBeUsed;
};

#endif // CONNECTDIALOG_H
