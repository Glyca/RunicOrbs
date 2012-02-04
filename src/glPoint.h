// glPoint.h: interface for the glPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLPOINT_H__ADADC708_0176_471A_8241_5DD4D700BCB2__INCLUDED_)
#define AFX_GLPOINT_H__ADADC708_0176_471A_8241_5DD4D700BCB2__INCLUDED_

#include <QtOpenGL>

class glPoint  
{
public:
	glPoint();
	virtual ~glPoint();

	GLfloat z;
	GLfloat y;
	GLfloat x;
};

#endif // !defined(AFX_GLPOINT_H__ADADC708_0176_471A_8241_5DD4D700BCB2__INCLUDED_)
