#include "GameWindow.h"
#include "version.h"

#include <QQuaternion>

GameWindow::GameWindow(ServerConnector* connector) : m_connector(connector)
{
	setAutoFillBackground(false);
}

void GameWindow::initializeGL()
{
	qDebug(tr("Initialized OpenGL, version %d.%d").toAscii(), format().majorVersion(), format().minorVersion());
	qDebug() << "OpenGL driver :" << (char*)glGetString(GL_VENDOR)<< "|" << (char*)glGetString(GL_RENDERER)<< "|" << (char*)glGetString(GL_VERSION);

	glShadeModel(GL_SMOOTH);
	glClearColor(138.0f / 255.0f, 219.0f / 255.0f, 206.0f / 255.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST); // test de profondeur
	glDepthFunc(GL_LEQUAL);  // Fontion du test de profondeur
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_CULL_FACE); // Optimisation
	glEnable(GL_LINE_SMOOTH); // Dessine de belles lignes
}

void GameWindow::paintEvent(QPaintEvent *event)
{
	setWindowTitle("CrafTuX");

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_MULTISAMPLE);
	static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	setCamera();

	render3D(); // 3D render

	glShadeModel(GL_FLAT);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// 2D render and flush
	QPainter painter(this);
	render2D(painter);
	painter.end();
}

void GameWindow::render2D(QPainter& painter)
{
	// TEXT
	QString text = "CrafTuX version " CRAFTUX_VERSION;
	QFontMetrics metrics = QFontMetrics(font());
	int border = qMax(4, metrics.leading());

	QRect rect = metrics.boundingRect(0, 0, width() - 2*border, int(height()*0.125), Qt::AlignCenter | Qt::TextWordWrap, text);
	painter.setRenderHint(QPainter::TextAntialiasing);
	painter.fillRect(QRect(0, 0, width(), rect.height() + 2*border), QColor(0, 0, 0, 127));
	painter.setPen(Qt::white);
	painter.fillRect(QRect(0, 0, width(), rect.height() + 2*border), QColor(0, 0, 0, 127));
	painter.drawText((width() - rect.width())/2, border, rect.width(), rect.height(), Qt::AlignCenter | Qt::TextWordWrap, text);

	QString postionText("Position : " + m_connector->me().v_position);
	painter.drawText(0, border, width() - border, rect.height(), Qt::AlignRight, postionText);

	QString directionText("Direction : " + m_connector->me().direction());
	painter.drawText(0, border*2 + rect.height(), width() - border, rect.height(), Qt::AlignRight, directionText);
}

void GameWindow::render3D()
{
	// Dessin de Ox ROUGE
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(60.0f, 0.0f, 0.0f);
	glEnd();
	// Oy VERT
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(60.0f, 60.0f, 0.0f);
	glEnd();
	// Oz BLEU
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(60.0f, 0.0f, 60.0f);
	glEnd();
}

void GameWindow::setCamera()
{
	GLfloat f_glMatrix[16];
	QQuaternion q; // Quaternion to create the OpenGl matrix

	QQuaternion q_pitch, q_heading;

	// Make the Quaternions that will represent our rotations
	q_pitch.fromAxisAndAngle(1, 0, 0, m_connector->me().pitch());
	q_heading.fromAxisAndAngle(0, 1, 0, m_connector->me().heading());

	q = q_pitch * q_heading;

	// m_glMatrix = q :
	{
		// First row
		f_glMatrix[ 0] = 1.0f - 2.0f * ( q.y() * q.y() + q.z() * q.z() );
		f_glMatrix[ 1] = 2.0f * (q.x() * q.y() + q.z() * q.scalar());
		f_glMatrix[ 2] = 2.0f * (q.x() * q.z() - q.y() * q.scalar());
		f_glMatrix[ 3] = 0.0f;

		// Second row
		f_glMatrix[ 4] = 2.0f * ( q.x() * q.y() - q.z() * q.scalar() );
		f_glMatrix[ 5] = 1.0f - 2.0f * ( q.x() * q.x() + q.z() * q.z() );
		f_glMatrix[ 6] = 2.0f * (q.z() * q.y() + q.x() * q.scalar() );
		f_glMatrix[ 7] = 0.0f;

		// Third row
		f_glMatrix[ 8] = 2.0f * ( q.x() * q.z() + q.y() * q.scalar() );
		f_glMatrix[ 9] = 2.0f * ( q.y() * q.z() - q.x() * q.scalar() );
		f_glMatrix[10] = 1.0f - 2.0f * ( q.x() * q.x() + q.y() * q.y() );
		f_glMatrix[11] = 0.0f;

		// Fourth row
		f_glMatrix[12] = 0;
		f_glMatrix[13] = 0;
		f_glMatrix[14] = 0;
		f_glMatrix[15] = 1.0f;
	}

	// Let OpenGL set our new prespective on the world!
	glMultMatrixf(f_glMatrix);
}
