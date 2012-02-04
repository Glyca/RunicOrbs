#ifndef ME_H
#define ME_H

#include "Player.h"
#include "glCamera.h"

class Me : public Player
{
public:
	Me();

private:
	glCamera* m_camera;
};

#endif // ME_H
