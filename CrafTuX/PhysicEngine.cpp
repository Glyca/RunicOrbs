#include "PhysicEngine.h"

CPhysicEngine* CPhysicEngine::c_PhysicEngine = 0;

CPhysicEngine::CPhysicEngine(QObject *parent) :
    QObject(parent)
{
    m_physicObjects.reserve(16);
    m_elapsedTimer.start();
    qDebug("Moteur physique construit");
}

CPhysicEngine* CPhysicEngine::getPhysicEngine()
{
    if(c_PhysicEngine == 0)
    {
	c_PhysicEngine = new CPhysicEngine;
    }
    return c_PhysicEngine;
}

PhysicObject* CPhysicEngine::createPhysicObject(preal mass)
{
    PhysicObject* po = new PhysicObject(mass);
    m_physicObjects.append(po);
    return po;
}

void CPhysicEngine::processMoves()
{
    foreach(PhysicObject* thePhysicObject, m_physicObjects)
    {
	thePhysicObject->processMove(m_elapsedTimer.elapsed() / 1000.0f);
    }

    // On redémarre le timer
    m_elapsedTimer.restart();
}
