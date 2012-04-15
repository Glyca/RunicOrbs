#include "GameWindow.h"
#include "blocks/TorchBlock.h"
#include "ClientConfiguration.h"
#include "PhysicEngine.h"
#include "ServerConnector.h"
#include "version.h"

GameWindow::GameWindow(ServerConnector* connector)
	: m_configuration(new ClientConfiguration()), m_connector(connector), b_playing(true), b_debugView(false), m_originalCursor(cursor()), m_inventoryPixmap(QPixmap(INVENTORY_SIZE * INVENTORY_SQUARE_SIZE, INVENTORY_SQUARE_SIZE))
{
	m_connector->world().physicEngine()->attach(m_connector->me());

	m_configuration->loadDefaultConfigFile();
	m_connector->world().setSeed(m_configuration->getSeed());
	m_connector->setViewDistance(m_configuration->getViewDistance());
	m_textureManager.setTextureFiltering((TextureManager::TextureFiltering)m_configuration->getTextureFiltering());
	setFps(m_configuration->getFps());
	setAutoFillBackground(false);
	setWindowTitle("CrafTuX");
	// Give us 10 torches to survive
	m_connector->me()->give(Blocks::TORCH.id(), 10);
	m_textureManager.loadItemImages();
	drawInventoryPixmap();

	// Every second, we load and prune the chunks
	connect(t_secondTimer, SIGNAL(timeout()), m_connector, SLOT(loadAndPruneChunks()));
	// Be notified when the inventory changes in order to redraw it
	connect(m_connector, SIGNAL(refreshInventory()), this, SLOT(drawInventoryPixmap()));
	resume();
}

void GameWindow::initializeGL()
{
	GLint maxTextureSize; glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
	qDebug(tr("Initialized OpenGL, version %d.%d").toAscii(), format().majorVersion(), format().minorVersion());
	qDebug() << "OpenGL driver :" << (const char*)glGetString(GL_VENDOR) << "|" << (const char*)glGetString(GL_RENDERER)<< "|" << (const char*)glGetString(GL_VERSION) << "| GL_MAX_TEXTURE_SIZE =" << maxTextureSize;

	m_textureManager.loadTextures();

	glClearColor(138.0f / 255.0f, 198.0f / 255.0f, 206.0f / 255.0f, 0.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);  // Fontion du test de profondeur
	if(m_configuration->getAntialiasing()) {
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_LINE_SMOOTH); // Dessine de belles lignes
		glEnable(GL_POLYGON_SMOOTH);
		glEnable(GL_MULTISAMPLE);
	}
	else {
		glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	}
	glLineWidth(2.5f);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT); // In all cases we start with flat
}

void GameWindow::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	m_connector->world().physicEngine()->processMoves();

	if(m_configuration->getSmoothShades()) glShadeModel(GL_SMOOTH); // re-enable
	glEnable(GL_DEPTH_TEST); // re-enable
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	setCamera();

	m_textureManager.bindTexture();
	render3D(); // 3D render
	m_textureManager.unbindTexture();

	if(m_configuration->getSmoothShades()) glShadeModel(GL_FLAT); // disable
	glDisable(GL_DEPTH_TEST);

	// 2D render and flush
	QPainter painter(this);
	render2D(painter);
	painter.end();
}

void GameWindow::render2D(QPainter& painter)
{
	// TEXT

	QFontMetrics metrics = QFontMetrics(font());
	int border = qMax(4, metrics.leading());
	painter.setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing, m_configuration->getAntialiasing() ? true : false);
	painter.setPen(Qt::white);

	if(b_playing) {
		QString text = QString("CrafTuX version " CRAFTUX_VERSION " @ ") + QString::number(getCurrentFPS()) + tr("FPS");
		if(b_debugView) {
			text.append("\n\n" + tr("Position : ") + m_connector->me()->v_position);
			text.append("\n" "Pitch : " + QString::number(m_connector->me()->pitch()) + " // Yaw : " + QString::number(m_connector->me()->yaw()));
			text.append("\n" "Block : " + m_connector->me()->pointedBlock() + " ID = " + QString::number(m_connector->world().block(m_connector->me()->pointedBlock())->id()));
			text.append("\n\nWorld seed = " + QString::number(m_connector->world().seed()));
			text.append("\nTouches floor = " + (m_connector->me()->touchesFloor() ? QString("true") : QString("false")));
			text.append("\nIs stuck = " + (m_connector->me()->isStuck() ? QString("true") : QString("false")));

			QRect rect = metrics.boundingRect(border, border, width(), height(), Qt::AlignLeft | Qt::TextWordWrap, text);
			painter.fillRect(QRect(0, 0, width(), rect.height() + border), QColor(0, 0, 0, 120));
			painter.drawText(border, border, rect.width(), rect.height(), Qt::AlignLeft | Qt::TextWordWrap, text);
		}
		else {
			painter.drawText(border, border, width(), height(), Qt::AlignLeft | Qt::TextWordWrap, text);
		}
		const int RETICLE_RADIUS = 5; // Draw the reticule :
		painter.drawLine((width() >> 1) - RETICLE_RADIUS, height() >> 1, (width() >> 1) + RETICLE_RADIUS, height() >> 1);
		painter.drawLine(width() >> 1, (height() >> 1) - RETICLE_RADIUS, width() >> 1, (height() >> 1) + RETICLE_RADIUS);
		// Draw the inventory :
		painter.drawPixmap((width() >> 1) - (m_inventoryPixmap.width() >> 1), height() - INVENTORY_SQUARE_SIZE - 5, m_inventoryPixmap);
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
	glBegin(GL_LINES);
	// Ox RED
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(60.0f, 0.0f, 0.0f);
	// Oy GREEN
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 60.0f, 0.0f);
	// Oz BLUE
	glColor3f(0.0f, 0.0f, 1.0f);
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
	glColor3ub(255, 255, 255); // Full white for the blocks
	m_connector->world().render3D();
}

void GameWindow::drawInventoryPixmap()
{
	const int SQUARE_BORDER_RADIUS = 20;
	const int SQUARE_BORDER = 2;
	m_inventoryPixmap.fill(Qt::transparent); // Erase all
	QPainter painter(&m_inventoryPixmap);
	painter.setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing, m_configuration->getAntialiasing() ? true : false);
	// To customize color and weight
	QPen pen;
	QFont font(painter.font());
	font.setWeight(QFont::DemiBold);
	font.setPixelSize(18);
	painter.setFont(font);

	for(unsigned int i = 0; i < INVENTORY_SIZE; ++i)
	{
		// Draw a square
		QRect slotRect(i * INVENTORY_SQUARE_SIZE + 1,
					   SQUARE_BORDER,
					   INVENTORY_SQUARE_SIZE - 2 * SQUARE_BORDER,
					   INVENTORY_SQUARE_SIZE - 2 * SQUARE_BORDER);
		if(m_connector->me()->inventorySlot(i).id() != 0) {
			// Draw the image of the block
			painter.drawImage(slotRect, Blocks::byId(m_connector->me()->inventorySlot(i).id()).itemImage());
			// Adjust the rectangle (add borders) and draw the amount we have in the slot
			QRect slotAmountLabelRect(slotRect);
			slotAmountLabelRect.adjust(-4, -4, -4, -4);
			pen.setColor(Qt::black);
			painter.setPen(pen);
			// 1 : draw a shadow
			painter.drawText(slotAmountLabelRect, Qt::AlignBottom | Qt::AlignRight, QString::number(m_connector->me()->inventorySlot(i).amount()));
			slotAmountLabelRect.adjust(-1, -1, -1, -1);
			pen.setColor(Qt::white);
			painter.setPen(pen);
			// 2 : then the real text
			painter.drawText(slotAmountLabelRect, Qt::AlignBottom | Qt::AlignRight, QString::number(m_connector->me()->inventorySlot(i).amount()));
		}
		// If this is the selected slot
		if(m_connector->me()->selectedSlot() == i) {
			pen.setColor(Qt::yellow);
			pen.setWidth(3);
			painter.setPen(pen);
		}
		else {
			pen.setColor(Qt::lightGray);
			pen.setWidth(2);
			painter.setPen(pen);
		}
		// Draw the border rectangle
		painter.drawRoundRect(slotRect, SQUARE_BORDER_RADIUS, SQUARE_BORDER_RADIUS);
	}
	painter.end();
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
		if(keyEvent->key() == m_configuration->getKey(ClientConfiguration::UP)) {
			m_connector->me()->walk(Entity::WalkDirection_Forward);
		}
		if(keyEvent->key() == m_configuration->getKey(ClientConfiguration::DOWN)) {
			m_connector->me()->walk(Entity::WalkDirection_Backward);
		}
		if(keyEvent->key() == m_configuration->getKey(ClientConfiguration::LEFT)) {
			m_connector->me()->walk(Entity::WalkDirection_Left);
		}
		if(keyEvent->key() == m_configuration->getKey(ClientConfiguration::RIGHT)) {
			m_connector->me()->walk(Entity::WalkDirection_Right);
		}
		if(keyEvent->key() == m_configuration->getKey(ClientConfiguration::JUMP)) {
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

	if(keyEvent->key() == Qt::Key_F3) {
		b_debugView = !b_debugView;
	}

	if(b_playing)
	{
		if(keyEvent->key() == m_configuration->getKey(ClientConfiguration::UP)) {
			m_connector->me()->stopWalking(Entity::WalkDirection_Forward);
		}
		if(keyEvent->key() == m_configuration->getKey(ClientConfiguration::DOWN)) {
			m_connector->me()->stopWalking(Entity::WalkDirection_Backward);
		}
		if(keyEvent->key() == m_configuration->getKey(ClientConfiguration::LEFT)) {
			m_connector->me()->stopWalking(Entity::WalkDirection_Left);
		}
		if(keyEvent->key() == m_configuration->getKey(ClientConfiguration::RIGHT)) {
			m_connector->me()->stopWalking(Entity::WalkDirection_Right);
		}
		if(keyEvent->key() == m_configuration->getKey(ClientConfiguration::JUMP)) {
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
			drawInventoryPixmap();
		}
		if(mouseEvent->button() == Qt::RightButton) {
			m_connector->useBlock();
			drawInventoryPixmap();
		}
	}
}

void GameWindow::wheelEvent(QWheelEvent* wheelEvent)
{
	int step = wheelEvent->delta() / 120;
	m_connector->selectSlot(m_connector->me()->selectedSlot() - step); // The check of the id validity is done in this function, so we don't care of it here
	wheelEvent->accept();
	drawInventoryPixmap();
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
