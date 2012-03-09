#include "LocalServerThread.h"

LocalServerThread::LocalServerThread()
{
	//TODO : initialize corectly a world
	m_world = new World(123, this);
}
