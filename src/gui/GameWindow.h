#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

#include "ClientConfiguration.h"
#include "GLWidget.h"
#include "ServerConnector.h"
#include "TextureManager.h"

class GameWindow : public GLWidget
{
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
	void mousePressEvent(QMouseEvent* mouseEvent);

	ClientConfiguration* m_configuration;
	ServerConnector* m_connector;
	TextureManager m_textureManager;

	void pause();
	void resume();

	bool b_playing; //! If the game is running (not paused)
	bool b_debugView; //! If debugging informations are shown
	QCursor m_originalCursor;
};

#endif // GAMEWINDOW_H
