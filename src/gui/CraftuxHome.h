#ifndef CRAFTUXHOME_H
#define CRAFTUXHOME_H

#include <QWidget>

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

private:
    Ui::CraftuxHome *ui;
};

#endif // CRAFTUXHOME_H
