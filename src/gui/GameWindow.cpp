#include "GameWindow.h"
#include "version.h"

GameWindow::GameWindow(ServerConnector* connector) : m_connector(connector), i_FPS(0), i_framesRenderedThisSecond(0)
{
	m_connector->world().physicEngine()->attach(m_connector->me());
	setAutoFillBackground(false);

	t_secondTimer = new QTimer(this);
	t_secondTimer->setInterval(1000);
	t_secondTimer->connect(t_secondTimer, SIGNAL(timeout()), this, SLOT(secondTimerTimeout()));
	t_secondTimer->start();

	setMouseTracking(true);
}

void GameWindow::initializeGL()
{
	qDebug(tr("Initialized OpenGL, version %d.%d").toAscii(), format().majorVersion(), format().minorVersion());
	qDebug() << "OpenGL driver :" << (char*)glGetString(GL_VENDOR) << "|" << (char*)glGetString(GL_RENDERER)<< "|" << (char*)glGetString(GL_VERSION);

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
	Q_UNUSED(event);
	m_connector->world().physicEngine()->processMoves();

	setWindowTitle("CrafTuX | " + QVariant(i_FPS).toString() + tr(" FPS"));

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	static GLfloat lightPosition[4] = { 0.5, 50.0, 7.0, 1.0 };
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

	i_framesRenderedThisSecond++; // We rendered a frame !
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

	QString pitchheadingText("Pitch : " + QVariant(m_connector->me()->pitch()).toString() + " // Yaw : " + QVariant(m_connector->me()->yaw()).toString());
	painter.drawText(border, border, width() - border, rect.height(), Qt::AlignLeft, pitchheadingText);
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
	Vector position = m_connector->me()->v_position;
	Vector direction = m_connector->me()->direction();
	gluLookAt(position.x, position.y, position.z,
			  position.x + direction.x, position.y + direction.y, position.z + direction.z,
			  0.0, 1.0, 0.0);
}

void GameWindow::keyPressEvent(QKeyEvent* keyEvent)
{
	if(keyEvent->key() == Qt::Key_Up)
	{
		m_connector->me()->walk(Entity::WalkDirection_Forward);
	}
	if(keyEvent->key() == Qt::Key_Down)
	{
		m_connector->me()->walk(Entity::WalkDirection_Backward);
	}
	if(keyEvent->key() == Qt::Key_Left)
	{
		m_connector->me()->walk(Entity::WalkDirection_Left);
	}
	if(keyEvent->key() == Qt::Key_Right)
	{
		m_connector->me()->walk(Entity::WalkDirection_Right);
	}
	if(keyEvent->key() == Qt::Key_0)
	{
		m_connector->me()->jump();
	}

	GLWidget::keyPressEvent(keyEvent);
}

void GameWindow::keyReleaseEvent(QKeyEvent* keyEvent)
{
	if(keyEvent->key() == Qt::Key_Up)
	{
		m_connector->me()->stopWalking(Entity::WalkDirection_Forward);
	}
	if(keyEvent->key() == Qt::Key_Down)
	{
		m_connector->me()->stopWalking(Entity::WalkDirection_Backward);
	}
	if(keyEvent->key() == Qt::Key_Left)
	{
		m_connector->me()->stopWalking(Entity::WalkDirection_Left);
	}
	if(keyEvent->key() == Qt::Key_Right)
	{
		m_connector->me()->stopWalking(Entity::WalkDirection_Right);
	}
	if(keyEvent->key() == Qt::Key_0)
	{
		m_connector->me()->stopJumping();
	}

	GLWidget::keyReleaseEvent(keyEvent);
}

void GameWindow::mouseMoveEvent(QMouseEvent* mouseEvent)
{
	const preal f_moveSpeed = 0.15f;

	GLfloat f_delta;
	int MouseX, MouseY;

	MouseX = mouseEvent->x();
	MouseY = mouseEvent->y();

	int CenterX = width() / 2;
	int CenterY = height() / 2;

	if(MouseX < CenterX)
	{
		f_delta = GLfloat(CenterX - MouseX);
		m_connector->me()->yaw(m_connector->me()->yaw() + f_moveSpeed * f_delta);
	}
	else if(MouseX > CenterX)
	{
		f_delta = GLfloat(MouseX - CenterX);
		m_connector->me()->yaw(m_connector->me()->yaw() - f_moveSpeed * f_delta);
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

void GameWindow::secondTimerTimeout()
{
	i_FPS = i_framesRenderedThisSecond;
	i_framesRenderedThisSecond = 0;
}
