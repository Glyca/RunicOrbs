#include "GameWindow.h"
#include "version.h"

GameWindow::GameWindow(ServerConnector* connector)
	: m_configuration(new ClientConfiguration()), m_connector(connector), i_FPS(0), i_framesRenderedThisSecond(0), b_playing(true), m_originalCursor(cursor())
{
	m_connector->world().physicEngine()->attach(m_connector->me());

	m_configuration->loadDefaultConfigFile();
	m_connector->world().setSeed(m_configuration->getSeed());
	setFps(m_configuration->getFps());

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
	qDebug() << "OpenGL driver :" << (const char*)glGetString(GL_VENDOR) << "|" << (const char*)glGetString(GL_RENDERER)<< "|" << (const char*)glGetString(GL_VERSION);

	m_textureManager.loadTextures();

	glClearColor(138.0f / 255.0f, 198.0f / 255.0f, 206.0f / 255.0f, 0.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);  // Fontion du test de profondeur
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glLineWidth(2.5f);
	glEnable(GL_LINE_SMOOTH); // Dessine de belles lignes
	glEnable(GL_TEXTURE_2D);

	// Lighting
	static GLfloat lightPosition[4] = { 0.0f, 256.0f, 0.0f, 1.0f };
	static GLfloat lightAmbient[4] = { 0.50f, 0.50f, 0.50f, 0.9f };
	static GLfloat lightDiffuse[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	static GLfloat lightSpecular[4] = { 0.015f, 0.015f, 0.015f, 0.05f };
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

	m_textureManager.bindTexture();
	render3D(); // 3D render
	m_textureManager.unbindTexture();

	glShadeModel(GL_FLAT); // disable
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

	glPushMatrix();
	BlockPosition pointedBlock = m_connector->me()->pointedBlock();
	glTranslatef(pointedBlock.x, pointedBlock.y, pointedBlock.z);
	glBegin(GL_LINES);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glEnd();
	glPopMatrix();

	// BLOCKS RENDER
	m_connector->world().render3D();
}

void GameWindow::setCamera()
{
	Vector position = m_connector->me()->eyePosition();
	Vector direction = m_connector->me()->direction();
	gluLookAt(position.x, position.y, position.z,
			  position.x + direction.x, position.y + direction.y, position.z + direction.z,
			  0.0, 1.0, 0.0);
}

void GameWindow::keyPressEvent(QKeyEvent* keyEvent)
{
	if(b_playing)
	{
		if(keyEvent->key() == Qt::Key_Z) {
			m_connector->me()->walk(Entity::WalkDirection_Forward);
		}
		if(keyEvent->key() == Qt::Key_S) {
			m_connector->me()->walk(Entity::WalkDirection_Backward);
		}
		if(keyEvent->key() == Qt::Key_Q) {
			m_connector->me()->walk(Entity::WalkDirection_Left);
		}
		if(keyEvent->key() == Qt::Key_D) {
			m_connector->me()->walk(Entity::WalkDirection_Right);
		}
		if(keyEvent->key() == Qt::Key_Space) {
			m_connector->me()->jump();
		}
	}

	GLWidget::keyPressEvent(keyEvent);
}

void GameWindow::keyReleaseEvent(QKeyEvent* keyEvent)
{
	if(keyEvent->key() == Qt::Key_Escape) {
		b_playing ? pause() : resume();
	}

	if(b_playing)
	{
		if(keyEvent->key() == Qt::Key_Z) {
			m_connector->me()->stopWalking(Entity::WalkDirection_Forward);
		}
		if(keyEvent->key() == Qt::Key_S) {
			m_connector->me()->stopWalking(Entity::WalkDirection_Backward);
		}
		if(keyEvent->key() == Qt::Key_Q) {
			m_connector->me()->stopWalking(Entity::WalkDirection_Left);
		}
		if(keyEvent->key() == Qt::Key_D) {
			m_connector->me()->stopWalking(Entity::WalkDirection_Right);
		}
		if(keyEvent->key() == Qt::Key_Space) {
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
		int mouseX, mouseY;

		mouseX = mouseEvent->x();
		mouseY = mouseEvent->y();

		int centerX = width() >> 1;
		int centerY = height() >> 1;

		if(mouseX < centerX) {
			f_delta = GLfloat(centerX - mouseX);
			m_connector->me()->yaw(m_connector->me()->yaw() + f_moveSpeed * f_delta);
		}
		else if(mouseX > centerX) {
			f_delta = GLfloat(mouseX - centerX);
			m_connector->me()->yaw(m_connector->me()->yaw() - f_moveSpeed * f_delta);
		}

		if(mouseY < centerY) {
			f_delta = GLfloat(centerY - mouseY);
			m_connector->me()->pitch(m_connector->me()->pitch() - f_moveSpeed * f_delta);
		}
		else if(mouseY > centerY) {
			f_delta = GLfloat(mouseY - centerY);
			m_connector->me()->pitch(m_connector->me()->pitch() + f_moveSpeed * f_delta);
		}

		QCursor newCursor(this->cursor());
		newCursor.setPos(mapToGlobal(QPoint(centerX, centerY)));
		this->setCursor(newCursor);
	}

	GLWidget::mouseMoveEvent(mouseEvent);
}

void GameWindow::mousePressEvent(QMouseEvent* mouseEvent)
{
	if(b_playing)
	{
		if(mouseEvent->button() == Qt::LeftButton) {
			m_connector->pickBlock();
		}
		if(mouseEvent->button() == Qt::RightButton) {
			m_connector->useBlock();
		}
	}
}

void GameWindow::pause()
{
	setCursor(m_originalCursor);
	setMouseTracking(false);
	b_playing = false;
}

void GameWindow::resume()
{
	QCursor newCursor(this->cursor());
	newCursor.setShape(Qt::BlankCursor);
	newCursor.setPos(width() >> 1, height() >> 1);
	setCursor(newCursor);
	setMouseTracking(true);
	b_playing = true;
}

void GameWindow::secondTimerTimeout()
{
	i_FPS = i_framesRenderedThisSecond;
	i_framesRenderedThisSecond = 0;
}
