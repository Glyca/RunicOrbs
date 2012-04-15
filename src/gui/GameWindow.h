#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "GLWidget.h"
#include "TextureManager.h"

class ClientConfiguration;
class ServerConnector;

const int INVENTORY_SQUARE_SIZE = 60; //!< The size of an item slot of the inventory

class GameWindow : public GLWidget
{
	Q_OBJECT
public:
	GameWindow(ServerConnector* connector);
	~GameWindow();

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
	void wheelEvent(QWheelEvent* wheelEvent);

	ClientConfiguration* m_configuration;
	ServerConnector* m_connector;
	TextureManager m_textureManager;

	void pause();
	void resume();

	bool b_playing; //!< If the game is running (not paused)
	bool b_debugView; //!< If debugging informations are shown
	QCursor m_originalCursor;
	QPixmap m_inventoryPixmap; //!< The inventory is redrawed only when selected item or contents are modified

private slots:
	void drawInventoryPixmap(); //!< Draw the inventory to the pixmap m_inventoryPixmap
};

#endif // GAMEWINDOW_H
