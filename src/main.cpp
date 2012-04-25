﻿#include <ctime>
#include <iostream> // std::cout
#include <QLibraryInfo>
#include <QLocale>
#include <QTextCodec>
#include <QTranslator>
#include <QtGui/QApplication>

#include "gui/ui/Home.h"
#include "Log.h"

int main(int argc, char *argv[])
{
	// initialize random seed
	srand(time(NULL));

	// On prend nos précautions pour les traductions
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

	Log::plugOutputStream(&std::cout); // Make the log be put in std::cout
	QApplication a(argc, argv);

	QTranslator qtTranslator;
	qtTranslator.load( "qt_" + QLocale::system().name(),
					   QLibraryInfo::location(QLibraryInfo::TranslationsPath) );
	a.installTranslator(&qtTranslator);

	QTranslator craftuxTranslator;
	craftuxTranslator.load("craftux_" + QLocale::system().name(), a.applicationDirPath() + "/lang/");
	a.installTranslator(&craftuxTranslator);

	Home w;
	w.show();
	return a.exec();
}
