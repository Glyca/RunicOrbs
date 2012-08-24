#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QLabel>

/*! This widget is displayed when loading a world */
class LoadingWidget : public QLabel
{
	Q_OBJECT
public:
	explicit LoadingWidget(QWidget *parent = 0);
	virtual ~LoadingWidget();

signals:

public slots:

};

#endif // LOADINGWIDGET_H
