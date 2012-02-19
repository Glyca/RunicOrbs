#include "GameWindow.h"
#include "version.h"

#include <QQuaternion>

GameWindow::GameWindow(ServerConnector* connector) : m_connector(connector)
{
	m_connector->world().physicEngine()->attach(m_connector->me());
	setAutoFillBackground(false);
	setMouseTracking(true);
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
	m_connector->world().physicEngine()->processMoves();

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

	QString postionText("Position : " + m_connector->me()->v_position);
	painter.drawText(0, border, width() - border, rect.height(), Qt::AlignRight, postionText);

	QString directionText("Direction : " + m_connector->me()->direction());
	painter.drawText(0, border*2 + rect.height(), width() - border, rect.height(), Qt::AlignRight, directionText);

	QString pitchheadingText("Pitch : " + QVariant(m_connector->me()->pitch()).toString() + " // Heading : " + QVariant(m_connector->me()->heading()).toString());
	painter.drawText(border, border*2 + rect.height(), width() - border, rect.height(), Qt::AlignLeft, pitchheadingText);
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
	glVertex3f(0.0f, 60.0f, 0.0f);
	glEnd();
	// Oz BLEU
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 60.0f);
	glEnd();

	// BLOCKS RENDER with a very very slow and old method for the moment
	m_connector->world().render3D();
}

void GameWindow::setCamera()
{
	GLfloat f_glMatrix[16];
	QQuaternion q; // Quaternion to create the OpenGl matrix

	QQuaternion q_pitch, q_heading;

	// Make the Quaternions that will represent our rotations
	q_pitch = QQuaternion::fromAxisAndAngle(1, 0, 0, m_connector->me()->pitch());
	q_heading = QQuaternion::fromAxisAndAngle(0, 1, 0, m_connector->me()->heading());

	q = q_pitch * q_heading;

	// http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation#Quaternion_to_Matrix

	float x2 = q.x() * q.x();
	float y2 = q.y() * q.y();
	float z2 = q.z() * q.z();
	float xy = q.x() * q.y();
	float xz = q.x() * q.z();
	float yz = q.y() * q.z();
	float wx = q.scalar() * q.x();
	float wy = q.scalar() * q.y();
	float wz = q.scalar() * q.z();

	// First row
	f_glMatrix[ 0] = 1.0f - 2.0f * (y2 + z2);
	f_glMatrix[ 1] =        2.0f * (xy - wz);
	f_glMatrix[ 2] =        2.0f * (xz + wy);
	f_glMatrix[ 3] = 0.0f;

	// Second row
	f_glMatrix[ 4] =        2.0f * (xy + wz);
	f_glMatrix[ 5] = 1.0f - 2.0f * (x2 + z2);
	f_glMatrix[ 6] =        2.0f * (yz - wx);
	f_glMatrix[ 7] = 0.0f;

	// Third row
	f_glMatrix[ 8] =        2.0f * (xz - wy);
	f_glMatrix[ 9] =        2.0f * (yz + wx);
	f_glMatrix[10] = 1.0f - 2.0f * (x2 + y2);
	f_glMatrix[11] = 0.0f;

	// Fourth row
	f_glMatrix[12] = 0;
	f_glMatrix[13] = 0;
	f_glMatrix[14] = 0;
	f_glMatrix[15] = 1.0f;

	// Let OpenGL set our new prespective on the world!
	glMultMatrixf(f_glMatrix);
	// and translate to our postion
	glTranslatef(-m_connector->me()->v_position.x, -m_connector->me()->v_position.y, -m_connector->me()->v_position.z);
}

void GameWindow::keyPressEvent(QKeyEvent* keyEvent)
{
	if(keyEvent->key() == Qt::Key_Up)
	{
		m_connector->me()->walk(Entity::WalkingDirection_Forward);
	}
	if(keyEvent->key() == Qt::Key_Down)
	{
		m_connector->me()->walk(Entity::WalkingDirection_Backward);
	}
	if(keyEvent->key() == Qt::Key_Left)
	{
		m_connector->me()->walk(Entity::WalkingDirection_Left);
	}
	if(keyEvent->key() == Qt::Key_Right)
	{
		m_connector->me()->walk(Entity::WalkingDirection_Right);
	}

	GLWidget::keyPressEvent(keyEvent);
}

void GameWindow::keyReleaseEvent(QKeyEvent* keyEvent)
{
	if(keyEvent->key() == Qt::Key_Up)
	{
		m_connector->me()->stopWalk(Entity::WalkingDirection_Forward);
	}
	if(keyEvent->key() == Qt::Key_Down)
	{
		m_connector->me()->stopWalk(Entity::WalkingDirection_Backward);
	}
	if(keyEvent->key() == Qt::Key_Left)
	{
		m_connector->me()->stopWalk(Entity::WalkingDirection_Left);
	}
	if(keyEvent->key() == Qt::Key_Right)
	{
		m_connector->me()->stopWalk(Entity::WalkingDirection_Right);
	}

	GLWidget::keyReleaseEvent(keyEvent);
}

void GameWindow::mouseMoveEvent(QMouseEvent* mouseEvent)
{
	const preal f_moveSpeed = 0.2f;

	GLfloat f_delta;
	int MouseX, MouseY;

	MouseX = mouseEvent->x();
	MouseY = mouseEvent->y();

	int CenterX = width() / 2;
	int CenterY = height() / 2;

	if(MouseX < CenterX)
	{
		f_delta = GLfloat(CenterX - MouseX);
		m_connector->me()->heading(m_connector->me()->heading() - f_moveSpeed * f_delta);
	}
	else if(MouseX > CenterX)
	{
		f_delta = GLfloat(MouseX - CenterX);
		m_connector->me()->heading(m_connector->me()->heading() + f_moveSpeed * f_delta);
	}

	if(MouseY < CenterY)
	{
		f_delta = GLfloat(CenterY - MouseY);
		m_connector->me()->pitch(m_connector->me()->pitch() - f_moveSpeed * f_delta);
	}
	else if(MouseY > CenterY)
	{
		f_delta = GLfloat(MouseY - CenterY);
		m_connector->me()->pitch(m_connector->me()->pitch() + f_moveSpeed * f_delta);
	}

	QCursor newCursor(this->cursor());
	newCursor.setPos(mapToGlobal(QPoint(CenterX, CenterY)));
	//newCursor.setShape(Qt::BlankCursor);
	this->setCursor(newCursor);
}
