#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "OpenGL.h"

class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit GLWidget(const int framesPerSecond = 60, QWidget *parent = 0, const char *name = "CrafTuX", QGLFormat format = GLWidget::defaultFormat());
	virtual void resizeGL(int width, int height);
	virtual void keyPressEvent(QKeyEvent* keyEvent);

	void toggleFullWindow();

	static QGLFormat defaultFormat();

public slots:
	virtual void timeOutSlot();
	void secondTimerTimeout();

protected:
	void setFps(const int targetFps);
	int getCurrentFPS();
	void resizeGLreally();
	int i_winheight, i_winwidth;
	float f_cameraAngle;
	QTimer* t_secondTimer;

private:
	QTimer* t_Timer;
	bool b_Fullscreen;
	int i_FPS; //! The current framerate
	int i_framesRenderedThisSecond; //! The number of frames that have already been rendered this second
};

#endif // GLWIDGET_H
