#include "GLWidget.h"

GLWidget::GLWidget(int framesPerSecond, QWidget *parent, char *name, QGLFormat format)
	: QGLWidget(format, parent), f_cameraAngle(45.0f), b_Fullscreen(false)
{
    setWindowTitle(QString::fromUtf8(name));
    if(framesPerSecond == 0)
        t_Timer = NULL;
    else
    {
        int seconde = 1000; // 1 seconde = 1000 ms
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start( timerInterval );
    }
}

void GLWidget::resizeGL(int width, int height)
{
	i_winwidth = width; i_winheight = height;
	resizeGLreally();
}

void GLWidget::resizeGLreally()
{
	if(i_winheight == 0)
		i_winheight = 1;
	glViewport(0, 0, i_winwidth, i_winheight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(f_cameraAngle, (GLfloat)i_winwidth/(GLfloat)i_winheight, 0.1f, 2000.0f);

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

