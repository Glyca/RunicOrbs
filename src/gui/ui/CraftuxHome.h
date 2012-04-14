#ifndef CRAFTUXHOME_H
#define CRAFTUXHOME_H

#include <QWidget>

class OptionsDialog;

namespace Ui {
	class CraftuxHome;
}

/*! The main menu of Craftux */
class CraftuxHome : public QWidget
{
	Q_OBJECT

public:
	explicit CraftuxHome(QWidget *parent = 0);
	~CraftuxHome();

private slots:
	void soloGameLaunch();
	void openOptions();
	void optionsClosed();
	void openConnectDialog();
	void openServerInterface();

private:
	Ui::CraftuxHome *ui;
	bool b_optionDialogOpened;
	OptionsDialog* m_optionsDialog;
};

#endif // CRAFTUXHOME_H
