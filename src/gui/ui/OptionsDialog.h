#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QSignalMapper>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMap>
#include "ClientConfiguration.h"

namespace Ui {
	class OptionsDialog;
}

class OptionsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit OptionsDialog(QWidget *parent = 0);
	~OptionsDialog();

	void keyPressEvent(QKeyEvent* keyEvent);

public slots:
	void onClick(QAbstractButton*);
	void changeKey(int);

private:

	ClientConfiguration config;

	/*! Enum for button color */
	enum Color{
		RED,
		BLUE,
		DEFAULT
	};

	QMap<Action,QPushButton*> m_actionToButtonMap;

	void load();
	void save();
	void refresh();
	void checkDoubleKey();
	void setButtonColor(Color color,Action action);
	void resetAllColor();
	void fillAction2ButtonMap();
	Ui::OptionsDialog *ui;
	int reallocationKey;
	bool reallocation;
	bool doubleKey; /*! If there is two meaning for one key */
};

#endif // OPTIONSDIALOG_H
