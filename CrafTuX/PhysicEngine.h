#ifndef PHYSICENGINE_H
#define PHYSICENGINE_H

#include <QObject>
#include <QList>
#include <QElapsedTimer>
#include "PhysicObject.h"

// Singloton class
class CPhysicEngine : public QObject
{
    Q_OBJECT
public:
    explicit CPhysicEngine(QObject *parent = 0);

    static class CPhysicEngine* c_PhysicEngine;
    static CPhysicEngine* getPhysicEngine();

    PhysicObject* createPhysicObject(preal mass = f_defaultMass);

    void processMoves();

signals:

public slots:

private:

    QElapsedTimer m_elapsedTimer;
    QList<PhysicObject*> m_physicObjects;

};

#define PhysicEngine (CPhysicEngine::getPhysicEngine())

#endif // PHYSICENGINE_H
