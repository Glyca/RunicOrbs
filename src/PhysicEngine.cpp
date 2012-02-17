#include "PhysicEngine.h"

PhysicEngine* PhysicEngine::c_PhysicEngine = 0;

PhysicEngine::PhysicEngine(QObject *parent) :
	QObject(parent)
{
	m_physicObjects.reserve(16);
	m_elapsedTimer.start();
	qDebug("Moteur physique construit");
}

PhysicEngine* PhysicEngine::getPhysicEngine()
{
	if(c_PhysicEngine == 0)
	{
		c_PhysicEngine = new PhysicEngine;
	}
	return c_PhysicEngine;
}

PhysicObject* PhysicEngine::createPhysicObject(preal mass)
{
	PhysicObject* po = new PhysicObject(mass);
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
