#ifndef CRAFTUXHOME_H
#define CRAFTUXHOME_H

#include <QWidget>

const int MAX_WORLD_X = 100, DEFAULT_WORLD_X = 30;
const int MAX_WORLD_Y = 128, DEFAULT_WORLD_Y = 64;
const int MAX_WORLD_Z = 100, DEFAULT_WORLD_Z = 30;
const int DEFAULT_WORLD_SEA = DEFAULT_WORLD_Y / 2;

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
    void localTestLaunch();

    void valueChangedX(int value);
    void valueChangedY(int value);
    void valueChangedZ(int value);
    void valueChangedSEA(int value);

private:
    Ui::CraftuxHome *ui;

    void calcBlockNumber();
};

#endif // CRAFTUXHOME_H
