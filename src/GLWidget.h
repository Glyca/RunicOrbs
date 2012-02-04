#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(int framesPerSecond = 25, QWidget *parent = 0, char *name = "CrafTuX", QGLFormat format = GLWidget::defaultFormat());
    virtual void initializeGL() = 0;
	virtual void resizeGL(int width, int height);
    virtual void paintGL() = 0;
    virtual void keyPressEvent( QKeyEvent *keyEvent );

    void toggleFullWindow();

    static QGLFormat defaultFormat();

public slots:
    virtual void timeOutSlot();

protected:
	void resizeGLreally();
	int i_winheight, i_winwidth;
	float f_cameraAngle;

private:

    QTimer *t_Timer;
    bool b_Fullscreen;


};

#endif // GLWIDGET_H
