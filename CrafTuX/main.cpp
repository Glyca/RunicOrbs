#include <QtGui/QApplication>
#include "CraftuxHome.h"

int main(int argc, char *argv[])
{
    // On prend nos précautions
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    CraftuxHome w;
    w.show();

    return a.exec();
}
