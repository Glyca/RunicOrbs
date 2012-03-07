#include "GLWidget.h"
#include "glextensions.h"

GLWidget::GLWidget(int framesPerSecond, QWidget *parent, char *name, QGLFormat format)
	: QGLWidget(format, parent), f_cameraAngle(70.0f), t_Timer(NULL), b_Fullscreen(false)
{
	setWindowTitle(QString::fromUtf8(name));
	setFps(framesPerSecond);
	makeCurrent(); // We have to make context current to resolve OpenGL functions (Fixes ISSUE 2)
	getGLExtensionFunctions().resolve(context()); // resolve OpenGL >1.5 functions (Fix for ISSUE 1)
}

void GLWidget::resizeGL(int width, int height)
{
	i_winwidth = width; i_winheight = height;
	resizeGLreally();
}

void GLWidget::setFps(const int targetFps)
{
	if(t_Timer != NULL) delete t_Timer;

	if(targetFps == 0)
		t_Timer = NULL;
	else
	{
		int seconde = 1000; // 1 seconde = 1000 ms
		int timerInterval = seconde / targetFps;
		t_Timer = new QTimer(this);
		connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
		t_Timer->start( timerInterval );
	}
}

void GLWidget::resizeGLreally()
{
	if(i_winheight == 0)
		i_winheight = 1;
	glViewport(0, 0, i_winwidth, i_winheight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(f_cameraAngle, (GLfloat)i_winwidth/(GLfloat)i_winheight, 0.2f, 2000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLWidget::keyPressEvent(QKeyEvent *keyEvent)
{
	switch(keyEvent->key())
	{
	case Qt::Key_C:
		close();
		break;

	case Qt::Key_F11:
		toggleFullWindow();
		break;
	}
}

void GLWidget::timeOutSlot()
{
	update();
}

void GLWidget::toggleFullWindow()
{
	if(b_Fullscreen)
	{
		showNormal();
		b_Fullscreen = false;
	}
	else
	{
		showFullScreen();
		b_Fullscreen = true;
	}
}


QGLFormat GLWidget::defaultFormat()
{
	QGLFormat format;
	format.setOption(QGL::DoubleBuffer | QGL::DepthBuffer | QGL::SampleBuffers);
	format.setVersion(1, 5);
	return format;
}

