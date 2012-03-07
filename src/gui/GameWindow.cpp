#include "GameWindow.h"
#include "version.h"

GameWindow::GameWindow(ClientConfiguration* configuration, ServerConnector* connector)
	: m_configuration(configuration), m_connector(connector), i_FPS(0), i_framesRenderedThisSecond(0), b_playing(true), m_originalCursor(cursor())
{
	m_connector->world().physicEngine()->attach(m_connector->me());
	setFps(configuration->getFps());
	setAutoFillBackground(false);

	t_secondTimer = new QTimer(this);
	t_secondTimer->setInterval(1000);
	t_secondTimer->connect(t_secondTimer, SIGNAL(timeout()), this, SLOT(secondTimerTimeout()));
	t_secondTimer->start();

	resume();
}

void GameWindow::initializeGL()
{
	qDebug(tr("Initialized OpenGL, version %d.%d").toAscii(), format().majorVersion(), format().minorVersion());
	qDebug() << "OpenGL driver :" << (char*)glGetString(GL_VENDOR) << "|" << (char*)glGetString(GL_RENDERER)<< "|" << (char*)glGetString(GL_VERSION);

	glClearColor(138.0f / 255.0f, 219.0f / 255.0f, 206.0f / 255.0f, 0.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);  // Fontion du test de profondeur
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH); // Dessine de belles lignes

	// Lighting
	static GLfloat lightPosition[4] = { 0.0f, 100.0f, 0.0f, 1.0f };
	static GLfloat lightAmbient[4] = { 0.2f, 0.2f, 0.2f, 0.5f };
	static GLfloat lightDiffuse[4] = { 0.05f, 0.05f, 0.05f, 0.05f };
	static GLfloat lightSpecular[4] = { 0.05f, 0.05f, 0.05f, 0.05f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL); // To mix light and colors
}

void GameWindow::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	m_connector->world().physicEngine()->processMoves();

	setWindowTitle("CrafTuX | " + QVariant(i_FPS).toString() + tr(" FPS"));

	glShadeModel(GL_SMOOTH); // re-enable
	glEnable(GL_DEPTH_TEST); // re-enable
	glEnable(GL_LIGHTING); // re-enable

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	setCamera();

	render3D(); // 3D render

	glShadeModel(GL_FLAT); // disnable
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	// 2D render and flush
	QPainter painter(this);
	render2D(painter);
	painter.end();

	i_framesRenderedThisSecond++; // We rendered a frame !
}

void GameWindow::render2D(QPainter& painter)
{
	// TEXT

	QFontMetrics metrics = QFontMetrics(font());
	int border = qMax(4, metrics.leading());
	painter.setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing);
	painter.setPen(Qt::white);

	if(b_playing)
	{
		QString text = "CrafTuX version " CRAFTUX_VERSION;

		QRect rect = metrics.boundingRect(0, 0, width() - 2*border, int(height()*0.125), Qt::AlignCenter | Qt::TextWordWrap, text);
		painter.fillRect(QRect(0, 0, width(), rect.height() + 2*border), QColor(0, 0, 0, 127));
		painter.fillRect(QRect(0, 0, width(), rect.height() + 2*border), QColor(0, 0, 0, 127));
		painter.drawText((width() - rect.width())/2, border, rect.width(), rect.height(), Qt::AlignCenter | Qt::TextWordWrap, text);

		QString postionText("Position : " + m_connector->me()->v_position);
		painter.drawText(0, border, width() - border, rect.height(), Qt::AlignRight, postionText);

		QString pitchheadingText("Pitch : " + QVariant(m_connector->me()->pitch()).toString() + " // Yaw : " + QVariant(m_connector->me()->yaw()).toString());
		painter.drawText(border, border, width() - border, rect.height(), Qt::AlignLeft, pitchheadingText);
	}
	else
	{
		QString text = tr("The game is paused\n\nYou can resume by pressing ESCAPE or quit with C.");
		QRect rect = metrics.boundingRect(0, 0, width(), height(), Qt::AlignCenter | Qt::AlignHCenter, text);
		painter.drawRoundedRect(rect.adjusted(-10, -10, 10, 10), 10.0, 10.0);
		painter.drawText(0, 0, width(), height(), Qt::AlignCenter | Qt::AlignHCenter, text);
	}
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

	// BLOCKS RENDER
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
	if(b_playing)
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
	}

	GLWidget::keyPressEvent(keyEvent);
}

void GameWindow::keyReleaseEvent(QKeyEvent* keyEvent)
{
	if(keyEvent->key() == Qt::Key_Escape)
	{
		if(b_playing)
		{
			pause();
		}
		else
		{
			resume();
		}
	}

	if(b_playing)
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
	}

	GLWidget::keyReleaseEvent(keyEvent);
}

void GameWindow::mouseMoveEvent(QMouseEvent* mouseEvent)
{
	if(b_playing)
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
		this->setCursor(newCursor);
	}

	GLWidget::mouseMoveEvent(mouseEvent);
}

void GameWindow::pause()
{
	this->setCursor(m_originalCursor);
	setMouseTracking(false);
	b_playing = false;
}

void GameWindow::resume()
{
	QCursor newCursor(this->cursor());
	newCursor.setShape(Qt::BlankCursor);
	newCursor.setPos(width() >> 1, height() >> 1);
	this->setCursor(newCursor);
	setMouseTracking(true);
	b_playing = true;
}

void GameWindow::secondTimerTimeout()
{
	i_FPS = i_framesRenderedThisSecond;
	i_framesRenderedThisSecond = 0;
}
