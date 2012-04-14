#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QAbstractButton>

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

private:
	Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
