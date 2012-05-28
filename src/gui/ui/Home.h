#ifndef CRAFTUXHOME_H
#define CRAFTUXHOME_H

#include <QWidget>

class OptionsDialog;
class ServerWidget;

namespace Ui {
	class Home;
}

/*! The main menu of Craftux */
class Home : public QWidget
{
	Q_OBJECT

public:
	explicit Home(QWidget *parent = 0);
	~Home();

private slots:
	void soloGameLaunch();
	void openOptions();
	void optionsClosed();
	void openConnectDialog();
	void openServerWidget();
	void serverWidgetClosed();

private:
	Ui::Home *ui;
	bool b_optionDialogOpened;
	OptionsDialog* m_optionsDialog;
	bool b_serverWidgetOpened;
	ServerWidget* m_serverWidget;
};

#endif // CRAFTUXHOME_H
