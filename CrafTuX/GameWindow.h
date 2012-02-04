#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "GLWidget.h"
#include "ServerConnector.h"

class GameWindow : public GLWidget
{
public:
	GameWindow(ServerConnector* connector);

	virtual void initializeGL();
	virtual void paintGL();

private:

	ServerConnector* m_connector;
};

#endif // GAMEWINDOW_H
