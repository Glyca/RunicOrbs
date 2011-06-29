#include "GLWidget.h"

GLWidget::GLWidget(int framesPerSecond, QWidget *parent, char *name, QGLFormat format)
    : QGLWidget(format, parent), b_Fullscreen(false)
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

