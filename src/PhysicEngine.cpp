#include "PhysicEngine.h"
#include "World.h"

PhysicEngine::PhysicEngine(World* world, QObject *parent) : QObject(parent), m_workingWorld(world)
{
	m_physicObjects.reserve(16);
	m_elapsedTimer.start();
	qDebug("PhysicEngine created (currently have %d PhysicObjects)", m_physicObjects.count());
}

PhysicObject* PhysicEngine::createPhysicObject(preal mass)
{
	PhysicObject* po = new PhysicObject(m_workingWorld, mass);
	this->attach(po);
	return po;
}

void PhysicEngine::processMoves()
{
	foreach(PhysicObject* thePhysicObject, m_physicObjects)
	{
		thePhysicObject->processMove(m_elapsedTimer.elapsed() / 1000.0, *m_workingWorld);
	}

	// On redémarre le timer
	m_elapsedTimer.restart();
}
