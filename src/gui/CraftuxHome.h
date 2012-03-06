#ifndef CRAFTUXHOME_H
#define CRAFTUXHOME_H

#include <QWidget>
#include "OptionsDialog.h"

namespace Ui {
	class CraftuxHome;
}

class CraftuxHome : public QWidget
{
	Q_OBJECT

public:
	explicit CraftuxHome(QWidget *parent = 0);
	~CraftuxHome();

public slots:
	void soloGameLaunch();
	void openOptions();
	void optionsClosed();

private:
	Ui::CraftuxHome *ui;
	bool b_optionDialogOpened;
	OptionsDialog* m_optionsDialog;
};

#endif // CRAFTUXHOME_H
