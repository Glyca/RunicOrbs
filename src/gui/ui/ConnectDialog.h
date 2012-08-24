#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

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
	~ConnectDialog();

public slots:
	void onClick(QAbstractButton*);
	void startGame();

private:
	Ui::ConnectDialog *ui;
	ServerConnector* m_connectorToBeUsed;
};

#endif // CONNECTDIALOG_H
