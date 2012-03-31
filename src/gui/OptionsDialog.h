#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QSignalMapper>
#include <QKeyEvent>
#include <QMessageBox>

namespace Ui {
    class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();
    enum Action{
        UP,
        DOWN,
        LEFT,
        RIGHT,
        JUMP,
        NBVAL
    };
    void keyPressEvent(QKeyEvent* keyEvent);

public slots:
    void onClick(QAbstractButton*);
    void changeKey(int);

private:
    void load();
    void save();
    void checkKey();
    Ui::OptionsDialog *ui;
    int reallocationKey;
    bool reallocation;
    bool doubleKey; /*! If there is two meaning for one key */
};

#endif // OPTIONSDIALOG_H
