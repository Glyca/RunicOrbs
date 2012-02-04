// glVector.h: interface for the glVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLVECTOR_H__F526A5CF_89B5_4F20_8F2C_517D83879D35__INCLUDED_)
#define AFX_GLVECTOR_H__F526A5CF_89B5_4F20_8F2C_517D83879D35__INCLUDED_

#include <QtOpenGL>

class glVector  
{
public:
	void operator *=(GLfloat scalar);
	glVector();
	virtual ~glVector();

	GLfloat k;
	GLfloat j;
	GLfloat i;
};

#endif // !defined(AFX_GLVECTOR_H__F526A5CF_89B5_4F20_8F2C_517D83879D35__INCLUDED_)
