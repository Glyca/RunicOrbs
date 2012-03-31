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
	PhysicObject* po = new PhysicObject(m_workingWorld, 0, mass);
	this->attach(po);
	return po;
}

void PhysicEngine::processMoves()
{
	foreach(PhysicObject* thePhysicObject, m_physicObjects)
	{
		thePhysicObject->processMove(m_elapsedTimer.elapsed() / 1000.0);
	}

	// On redémarre le timer
	m_elapsedTimer.restart();
}

const PhysicObject* PhysicEngine::po(const int id) const
{
	for(int i = 0; i < m_physicObjects.size(); ++i) {
		if(m_physicObjects.value(i)->id() == id) {
			return m_physicObjects.value(i);
		}
	}
	return NULL;
}
