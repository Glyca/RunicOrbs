#include "GameWindow.h"

GameWindow::GameWindow(ServerConnector* connector) : m_connector(connector)
{
}

void GameWindow::initializeGL()
{
	qDebug() << "L'initialisation d'OpenGL a réussi";
	qDebug("OpenGL>Window_version : %d.%d", format().majorVersion(), format().minorVersion());
	qDebug() << "OpenGL>Vendor :" << (char*)glGetString(GL_VENDOR);
	qDebug() << "OpenGL>Renderer :" << (char*)glGetString(GL_RENDERER);
	qDebug() << "OpenGL>Version :" << (char*)glGetString(GL_VERSION);

	GLint max_lights; glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
	qDebug() << "OpenGL>Max Lights :" << max_lights;

	glShadeModel(GL_SMOOTH);
	glClearColor(138.0f / 255.0f, 219.0f / 255.0f, 206.0f / 255.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST); // test de profondeur
	glDepthFunc(GL_LEQUAL);  // Fontion du test de profondeur
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_CULL_FACE); // Optimisation
	glEnable(GL_LINE_SMOOTH); // Dessine de belles lignes
}

void GameWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0f, 1.0f ,1.0f); // On écrit les infos en blanc
}
