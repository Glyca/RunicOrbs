#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

#include "GLWidget.h"
#include "ServerConnector.h"

class GameWindow : public GLWidget
{
	Q_OBJECT

public:
	GameWindow(ServerConnector* connector);

private:
	void initializeGL();
	void paintEvent(QPaintEvent* event);

	void render2D(QPainter& painter);
	void render3D();

	void setCamera();

	void keyPressEvent(QKeyEvent* keyEvent);
	void keyReleaseEvent(QKeyEvent* keyEvent);
	void mouseMoveEvent(QMouseEvent* mouseEvent);

	ServerConnector* m_connector;

	QTimer* t_secondTimer;
	int i_FPS, i_framesRenderedThisSecond;
private slots:
	void secondTimerTimeout();
};

#endif // GAMEWINDOW_H
