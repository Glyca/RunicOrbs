#include <cstdio>
#include <cstdlib>
#include <QtGui/QApplication>

#include "CraftuxHome.h"

void craftuxMessageOutput(QtMsgType type, const char* msg)
{
	switch (type) {
	case QtDebugMsg:
		fprintf(stderr, QObject::tr("[Debug] %s\n").toAscii(), msg);
		break;
	case QtWarningMsg:
		fprintf(stderr, QObject::tr("[Warning] %s\n").toAscii(), msg);
		break;
	case QtCriticalMsg:
		fprintf(stderr, QObject::tr("[Critical] %s\n").toAscii(), msg);
		break;
	case QtFatalMsg:
		fprintf(stderr, QObject::tr("[Fatal] %s\n").toAscii(), msg);
		abort();
	}
}

int main(int argc, char *argv[])
{
	// On prend nos précautions pour les traductions
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

	qInstallMsgHandler(craftuxMessageOutput);

	QApplication a(argc, argv);
	CraftuxHome w;
	w.show();

	return a.exec();
}
